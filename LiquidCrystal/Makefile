# Makefile - A makefile for the project
#
# Matt Staniszewski
# EE 542

C = gcc

CFLAGS =

LD = gcc

LDFLAGS =

lcd_test: LiquidCrystal.o wiringPi.o spi.o lcd_test.o
	$(LD) $(LDFLAGS) -o lcd_test LiquidCrystal.o wiringPi.o spi.o lcd_test.o

LiquidCrystal.o: LiquidCrystal.c LiquidCrystal.h
	$(C) $(CFLAGS) -c -o LiquidCrystal.o LiquidCrystal.c

wiringPi.o: wiringPi/wiringPi.c wiringPi/wiringPi.h
	$(C) $(CFLAGS) -c -o wiringPi.o wiringPi/wiringPi.c

spi.o: nodeSPI/spi.c nodeSPI/spi.h
	$(C) $(CFLAGS) -c -o spi.o nodeSPI/spi.c

lcd_test.o: lcd_test.c
	$(C) $(CFLAGS) -c -o lcd_test.o lcd_test.c

clean: 
	rm -f LiquidCrystal.o wiringPi.o spi.o lcd_test.o lcd_test

test: lcd_test 
	./lcd_test

all: lcd_test

