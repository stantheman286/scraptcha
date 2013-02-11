/*
 Demonstration sketch for Adafruit i2c/SPI LCD backpack
 using 74HC595 SPI expander
 ( http://www.ladyada.net/products/i2cspilcdbackpack/index.html )

 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * 5V to Arduino 5V pin
 * GND to Arduino GND pin
 * CLK to Digital 2
 * DAT to Digital 3
 * LAT to Digital 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// include the library code:
//ms #include "Wire.h"
#include "LiquidCrystal.h"
#include "wiringPi/wiringPi.h"
#include "nodeSPI/spi.h"

void lcdSetup(int fd) {
  // set up the LCD's number of rows and columns: 
  begin(fd, 16, 2, LCD_5x8DOTS);
  // Print a message to the LCD.
  print(fd, "hello, world!");

}

void loop(int fd) {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  setCursor(fd, 0, 1);
  // print the number of seconds since resets

  print(fd, "*");

  setBacklight(fd, HIGH);
  delay(500);
  setBacklight(fd, LOW);
  delay(500);
}

int main(void) {

  int fd = open("/dev/spidev0.1", O_RDWR);

  if (fd < 0) {
    printf("Could not open SPI device\n");
    return -1;
  }

  if (wiringPiSetup() == -1) {
    printf("Could not set up wiringPi\n");
    return -1;
  }

  setup(fd, 3, 2, 4);
  lcdSetup(fd);
  
  while(1)
    loop(fd);

}

