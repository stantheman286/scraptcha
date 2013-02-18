# Makefile - A makefile for the project
#
# Matt Staniszewski
# EE 542

C = gcc

CFLAGS =

CFLAGS_WEBCAM = `pkg-config --cflags --libs opencv`

LD = gcc

LDFLAGS =

LDFLAGS_WEBCAM = `pkg-config --cflags --libs opencv`

all: lcd led webcam

# Common functions
wiringPi.o: wiringPi/wiringPi.c wiringPi/wiringPi.h
	$(C) $(CFLAGS) -c -o wiringPi.o wiringPi/wiringPi.c

spi.o: nodeSPI/spi.c nodeSPI/spi.h
	$(C) $(CFLAGS) -c -o spi.o nodeSPI/spi.c

# LCD
lcd: lcd.o wiringPi.o spi.o
	$(LD) $(LDFLAGS) -o lcd lcd.o wiringPi.o spi.o

lcd.o: lcd.c lcd.h
	$(C) $(CFLAGS) -c -o lcd.o lcd.c

# LEDs
led: wiringPi.o led.o
	$(LD) $(LDFLAGS) -o led wiringPi.o led.o

led.o: led.c
	$(C) $(CFLAGS) -c -o led.o led.c

# Webcam
webcam: webcam.c
	$(LD) $(LDFLAGS_WEBCAM) -o webcam webcam.c

# Cleanup and testing
clean: 
	rm -f wiringPi.o spi.o lcd.o lcd led.o led webcam *.jpg

test: led
	./led
