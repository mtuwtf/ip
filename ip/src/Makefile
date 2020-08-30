# $Id: $

all: ip
file=ip
ip:  $(file).c
	cc -I/usr/include -I/usr/local/include -c -o $(file).o $(file).c && cc -static -L/usr/local/lib -o $(file) $(file).o -lkcgihtml -lkcgi -lz

check: all
	./ip | grep "Current IP Address"
	@echo "*** ALL TESTS PASSED ***"

clean:
	-rm $(file)

install:
	doas install -o www -g www -m 0500 ${file} /var/www/cgi-bin
	doas install -o www -g www -m 0444 ${file}.html /var/www/htdocs
	doas rm -f ${file}.o

.PHONY: call clean check install
