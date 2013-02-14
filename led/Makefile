# Makefile - A makefile for the project
#
# Matt Staniszewski
# EE 542

C = gcc

CFLAGS =

LD = gcc

LDFLAGS =

led_test: wiringPi.o led.o
	$(LD) $(LDFLAGS) -o led_test wiringPi.o led.o

wiringPi.o: wiringPi/wiringPi.c wiringPi/wiringPi.h
	$(C) $(CFLAGS) -c -o wiringPi.o wiringPi/wiringPi.c

led.o: led.c
	$(C) $(CFLAGS) -c -o led.o led.c

clean: 
	rm -f wiringPi.o led.o led_test

test: led_test 
	./led_test

all: led_test

