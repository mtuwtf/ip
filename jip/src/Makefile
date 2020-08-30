# $Id: $

all: jip
file=jip
jip:  $(file).c
	cc -I/usr/include -I/usr/local/include -c -o $(file).o $(file).c && cc -static -L/usr/local/lib -o $(file) $(file).o -lkcgi -lkcgijson -lz

check: all
	./jip | grep "ip"
	@echo "*** ALL TESTS PASSED ***"

clean:
	-rm $(file)

install:
	doas install -o www -g www -m 0500 ${file} /var/www/cgi-bin
	doas rm -f ${file}.o

.PHONY: call clean check install
