CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=

drdupe:
	$(CC) $(CFLAGS) -o drdupe main.c $(LIBS)