all: bounce1d

clean:
	rm -f bounce1d bounce2d

bounce1d: bounce1d.c set_ticker.c
	cc bounce1d.c set_ticker.c -lcurses -o bounce1d

bounce2d: bounce2d.c set_ticker.c
	cc bounce2d.c set_ticker.c -lcurses -o bounce2d
