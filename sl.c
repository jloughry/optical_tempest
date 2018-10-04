// sl.c -- a covert channel using the Caps Lock LED.

// Requires: a Linux operating system
// Compile with: gcc -Wall -Werror -o sl sl.c
// Run with: ./sl

#include <linux/kd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define SCROLL_LOCK_LED 1
#define NUM_LOCK_LED    2
#define CAPS_LOCK_LED   4

#define SPEED 50 // This is the data transmission speed in bits per second.
#define LED_TO_USE CAPS_LOCK_LED

void get_LED_flags(char *current_led_flags);
void set_LED_flags(char current_led_flags);
void turn_on_LED(char which_LED);
void turn_off_LED(char which_LED);
void wait_one_bit_interval(void);
void send_a_bit_out_the_LED(char which_LED, int bit_value);

int main (void) {
  char message[] = "My credit card number is 4716 3164 6296 3163";

  // First, save the state of the keyboard LEDs so we can restore them later.
  char restore_state;
  get_LED_flags(&restore_state);

  // Transmit the message a character at a time.
  char *p = &message[0];
  while (*p) {
    // start bit is always a "1".
    send_a_bit_out_the_LED(LED_TO_USE, 1);

    // Send all 8 bits of the character, least significant bit first.
    for (int i = 0; i < 8; i++) {
      int bit_to_send = *p >> i & 0x01; // Extract a single bit.
      send_a_bit_out_the_LED(LED_TO_USE, bit_to_send);
    }

    // Stop bit is always a "0".
    send_a_bit_out_the_LED(LED_TO_USE, 0);

    p++; // Do the next character in the message.
  }

  // Restore state of the keyboard LEDs before we quit.
  set_LED_flags(restore_state);

  return EXIT_SUCCESS;
}

void get_LED_flags(char *current_led_flags) {
  if (ioctl(0, KDGETLED, current_led_flags)) {
    perror("ioctl KDGETLED");
    exit(EXIT_FAILURE);
  }
}

void set_LED_flags(char new_led_flags) {
  if (ioctl(0, KDSETLED, new_led_flags)) {
    perror("ioctl KDSETLED");
    exit(EXIT_FAILURE);
  }
}

void turn_on_LED(char which_LED) {
  char flags = 0;

  get_LED_flags(&flags);
  flags |= which_LED;
  set_LED_flags(flags);
}

void turn_off_LED(char which_LED) {
  char flags = 0;

  get_LED_flags(&flags);
  flags &= ~which_LED;
  set_LED_flags(flags);
}

void send_a_bit_out_the_LED(char which_LED, int bit_value) {
  switch (bit_value) {
    case 0:
      turn_off_LED(which_LED);
      break;
    case 1:
      turn_on_LED(which_LED);
      break;
    default:
      printf("In file %s at line %d, this should never happen.\n",
        __FILE__, __LINE__);
      exit(EXIT_FAILURE);
      break;
  }
  wait_one_bit_interval();
}

void wait_one_bit_interval(void) {
  usleep(1000000 / SPEED);
}

