# orno-reader
Orno WE-504 Power meter reader written in pure C.

This program was designed to read ORNO WE-504 on embedded
systems - such as Tomato, OpenWRT etc.

Application is very simple, just build it by typing
make
and run by typing ./orno-reader.

It will try to connect to ORNO reader via first USB serial
port (ttyUSB0), and if it succeeds, prints readed values
in human readable format.

Orno-Reader uses simple serial port control library from: 
http://www.teuniz.net/RS-232/.
