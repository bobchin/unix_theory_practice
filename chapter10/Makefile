all: clean

clean:
	rm -rf listargs stdinredir1 stdinredir2 whotofile \
		pipedemo pipedemo2

listargs: listargs.c
	cc listargs.c -o listargs

stdinredir1: stdinredir1.c
	cc stdinredir1.c -o stdinredir1

stdinredir2: stdinredir2.c
	cc stdinredir2.c -o stdinredir2

whotofile: whotofile.c
	cc whotofile.c -o whotofile

pipedemo: pipedemo.c
	cc pipedemo.c -o pipedemo

pipedemo2: pipedemo2.c
	cc pipedemo2.c -o pipedemo2
