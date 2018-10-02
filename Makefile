target = sl

CC = gcc
CFLAGS = -Wall -Werror
LFLAGS = 
EDITOR = vi

$(target): $(target).c
	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)

clean:
	rm -fv $(target)

test:
	./$(target)

vi:
	$(EDITOR) $(target).c

