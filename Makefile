CC        = gcc
CFLAGS    = -Wall -Wextra -g3 -fsanitize=address,undefined
PKGFLAGS  != pkg-config --cflags --libs sdl2


build:
	$(CC) $(CFLAGS) -o raycast src/*.c $(PKGFLAGS) -lm

run:
	./raycast

clean:
	rm -f raycast