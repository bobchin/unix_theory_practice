all: clean

clean:
	rm -rf smsh1 smsh2

smsh1: smsh1.c spliteline.c execute.c
	cc smsh1.c spliteline.c execute.c -o smsh1

smsh2: smsh2.c spliteline.c execute.c process.c controlflow.c
	cc smsh2.c spliteline.c execute.c process.c controlflow.c -o smsh2
