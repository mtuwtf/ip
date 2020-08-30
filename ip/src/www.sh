#!/bin/ksh
# $Id: $

if [ $# -lt 1 ]; then
    echo $0 program to compile
    exit
fi

FILE=$1

doas install -o www -g www -m 0500 ${FILE} /var/www/cgi-bin
doas install -o www -g www -m 0444 ${FILE}.html /var/www/htdocs
doas rm -f ${FILE}.o
