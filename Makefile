CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=

drdupe: src/main.c
	$(CC) $(CFLAGS) -o drdupe src/main.c $(LIBS)