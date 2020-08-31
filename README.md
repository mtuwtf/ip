# ip
Do it yourself "whatismyip" written in C using BCHS and KCGI

This was one of the first things I wrote while trying to learn how to use KCGI. There are two components that can be used independently: (ip) returns your IP in HTML and (jip) in JSON format. I use this mainly for my dynamic IP addresses that change from time to time to update DYN DNS.

This work would not have been possible without the amazing work by Kristaps Dzonsons, the author of kcgi - https://kristaps.bsd.lv/kcgi/. Kristaps is brilliant! I admire and appreciate all of his work. Anyone using my project's code would be best served by reading about the BCHS STACK - https://learnbchs.org/.

This project will assume that you are going to run this on OpenBSD using the default web server, httpd. It is not a must but I strongly recommend doing so for reasons that I will not go into here.

Install the latest release of [OpenBSD](https://www.openbsd.org). As of this writing that would be [OpenBSD 6.7](https://www.openbsd.org/67.html). I run all most of my systems on the AMD64 architecture. You will need to install the following stable package:
```
kcgi-0.12.0p0          <-- minimal CGI library for web applications
```
## changes specific to your environment
```
Checkout this repository: git@github.com:mtuwtf/ip.git
[t] ip $ tree
.
|-- LICENSE
|-- README.md
|-- ip
|   |-- Makefile
|   `-- src
|       |-- Makefile
|       |-- build.sh
|       |-- dev.css
|       |-- ip.c
|       |-- ip.html
|       |-- ip.sh
|       |-- make.sh
|       `-- www.sh
`-- jip
    |-- Makefile
    `-- src
        |-- Makefile
        |-- build.sh
        |-- jip.c
        |-- make.sh
        `-- www.sh

4 directories, 17 files
```
**cd ip/src && chmod 700 \*.sh && cd -**

**cd jip/src && chmod 700 \*.sh && cd -**

### ip

There are some changes that you will need to make in **ip/src/ip.html**.
Find and update the following sections in **ip/src/ip.html**.
```
<!-- CHANGE ME BELOW -->
<title>ip.example.com</title>
       ^^^^^^^^^^^^^^ replace this with your own web server's FQDN.

<!-- CHANGE ME BELOW -->
<meta name="description" content="ip.example.com">
                                  ^^^^^^^^^^^^^^ replace this with your own web server's FQDN.

<link rel="stylesheet" type="text/css" href="./dev.css">
                                               ^^^^^^^ replace this, if you want to replace this with your own CSS.

<body alink="#7e7e7e" background="./i/bg.jpg" bgcolor="#ffffff" link="#990099" vlink="#7e7e7e">
                                      ^^^^^^ this image just provides a bit of colour.

If you don't change any of the above, it will not break anything. The post to the compiled binary will work just fine.
```

## Compiling the C binaries

Now go into each of the following directories:
```
|-- ip
|   |-- Makefile
|   `-- src
|       |-- Makefile
|       |-- build.sh
|       |-- dev.css
|       |-- ip.c
|       |-- ip.html
|       |-- ip.sh
|       |-- make.sh
|       `-- www.sh
`-- jip
    |-- Makefile
    `-- src
        |-- Makefile
        |-- build.sh
        |-- jip.c
        |-- make.sh
        `-- www.sh
```
**cd ip/src && ./build.sh ip**

**cd ../../jip/src && ./build.sh jip**

If there were no errors during compilation, then those two files would be sitting in this directory with the following permisions:

**cd /var/www/cgi-bin***
```
[t] cgi-bin # ls -l ip jip
-r-x------  1 www  www  1181144 Aug 29 18:17 ip
-r-x------  1 www  www  1207528 Aug 29 18:48 jip
```


You should also check the ip.html. It should have the following permissions:

**cd /var/www/htdocs*
```
[t] htdocs # ls -l ip.html
-r--r--r--  1 www  www  926 Aug 29 18:17 ip.html
```

## Web Server set up

Assuming your dev machine has a public IP address and is accessible on the Internet.

Here is an example of my `/etc/httpd.conf` config on my dev machine:

```
# $Id: httpd.conf 503 2019-11-16 01:21:46Z mtu $

prefork 4

server "ip.mtu.wtf" {
        listen on * port 80
        listen on * tls port 443
        tls certificate "/etc/ssl/acme/wtf/ip.mtu.wtf.fullchain.pem"
        tls key "/etc/ssl/acme/wtf/ip.mtu.wtf.key"
        hsts
        root "/htdocs/"

        location "/cgi-bin/*" {
                fastcgi
                root "/"
        }
        location "/.well-known/acme-challenge/*" {
                root "/acme"
                request strip 2
                directory no auto index
        }
}
```
**Note: You will need to change the `server "ip.mtu.wtf" {` line to suit your environment. I'm assuming you also know how to set up Let's Encrypt to allow for TLS connections. Don't forget to update the *.pem* and *.key* files respectively **

Your `/etc/rc.conf.local` file should have these two entries:

httpd_flags=

slowcgi_flags=

There are some pictures on the [Wiki](https://github.com/mtuwtf/ip/wiki) to show what this will appear like.
