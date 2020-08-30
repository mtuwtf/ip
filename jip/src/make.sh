#!/bin/ksh
# $Id: $

if [ $# -lt 1 ]; then
    echo $0 program to compile
    exit
fi

FILE=$1

cc -I/usr/include -I/usr/local/include -c -o ${FILE}.o ${FILE}.c && cc -static -L/usr/local/lib -o ${FILE} ${FILE}.o -lkcgi -lkcgijson -lz

doas install -o www -g www -m 0500 ${FILE} /var/www/cgi-bin
doas rm -f ${FILE}.o
