all: bounce1d

clean:
	rm -f bounce1d

bounce1d: bounce1d.c set_ticker.c
	cc -o bounce1d bounce1d.c set_ticker.c -lcurses
