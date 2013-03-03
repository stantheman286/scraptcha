#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>

//ms: Additional libraries to support our Pi setup
#include "wiringPi/wiringPi.h"
#include "nodeSPI/spi.h"
#include "lcd.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//

//int main(int argc, char *argv[]) {
int lcdTest() {

  int fd;

  // Run init sequence and get descriptor
  fd = lcdStart();

  // Print a message to the LCD.
  lcdPrint(fd, "hello, world!");

  return 0;
}

// Starts the LCD to make it ready for use
int lcdStart() {
  
  int fd = open("/dev/spidev0.1", O_RDWR);

  if (fd < 0) {
    printf("Could not open SPI device\n");
    return -1;
  }

  if (wiringPiSetup() == -1) {
    printf("Could not set up wiringPi\n");
    return -1;
  }

  lcdSetup(fd, 3, 2, 4);
  
  // set up the LCD's number of rows and columns: 
  lcdBegin(fd, 16, 2, LCD_5x8DOTS);
 
  return fd;

}

void lcdSetup(int fd, uint8_t data, uint8_t clock, uint8_t latch ) {

  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
  // the SPI expander pinout
  _rs_pin = 1;
  _rw_pin = 255;
  _enable_pin = 2;
  _data_pins[0] = 6;  // really d4
  _data_pins[1] = 5;  // really d5
  _data_pins[2] = 4;  // really d6
  _data_pins[3] = 3;  // really d7
  
  _SPIdata = data;
  _SPIclock = clock;
  _SPIlatch = latch;

  _SPIbuff_tx = 0;

  // we can't lcdBegin() yet :(
  lcdBegin(fd, 16, 1, LCD_5x8DOTS);
}


void lcdInit(int fd, uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
			 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 

  _SPIclock = _SPIdata = _SPIlatch = 255;

  if (fourbitmode)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
  lcdBegin(fd, 16, 1, LCD_5x8DOTS);  
}

void lcdBegin(int fd, uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (_SPIclock != 255) {
    _SPIbuff_tx = 0x80; // backlight
  }

  if (lines > 1) {
    _displayfunction |= LCD_2LINE;
  }
  _numlines = lines;
  _currline = 0;

  // for some 1 line displays you can select a 10 pixel high font
  if ((dotsize != 0) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  _lcdDigitalWrite(fd, _rs_pin, LOW);
  _lcdDigitalWrite(fd, _enable_pin, LOW);
  if (_rw_pin != 255) { 
    _lcdDigitalWrite(fd, _rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (_displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    lcdWrite4bits(fd, 0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    lcdWrite4bits(fd, 0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    lcdWrite4bits(fd, 0x03); 
    delayMicroseconds(150);

    // finally, set to 8-bit interface
    lcdWrite4bits(fd, 0x02); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    lcdCommand(fd, LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(4500);  // wait more than 4.1ms

    // second try
    lcdCommand(fd, LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(150);

    // third go
    lcdCommand(fd, LCD_FUNCTIONSET | _displayfunction);
  }

  // finally, set # lines, font size, etc.
  lcdCommand(fd, LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  lcdDisplay(fd);

  // clear it off
  lcdClear(fd);

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  lcdCommand(fd, LCD_ENTRYMODESET | _displaymode);

}

/********** high level commands, for the user! */
void lcdClear(int fd)
{
  lcdCommand(fd, LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void lcdHome(int fd)
{
  lcdCommand(fd, LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void lcdSetCursor(int fd, uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row > _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }
  
  lcdCommand(fd, LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void lcdNoDisplay(int fd) {
  _displaycontrol &= ~LCD_DISPLAYON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcdDisplay(int fd) {
  _displaycontrol |= LCD_DISPLAYON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void lcdNoCursor(int fd) {
  _displaycontrol &= ~LCD_CURSORON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcdCursor(int fd) {
  _displaycontrol |= LCD_CURSORON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void lcdNoBlink(int fd) {
  _displaycontrol &= ~LCD_BLINKON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void lcdBlink(int fd) {
  _displaycontrol |= LCD_BLINKON;
  lcdCommand(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void lcdScrollDisplayLeft(int fd) {
  lcdCommand(fd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void lcdScrollDisplayRight(int fd) {
  lcdCommand(fd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void lcdLeftToRight(int fd) {
  _displaymode |= LCD_ENTRYLEFT;
  lcdCommand(fd, LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void lcdRightToLeft(int fd) {
  _displaymode &= ~LCD_ENTRYLEFT;
  lcdCommand(fd, LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void lcdAutoscroll(int fd) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  lcdCommand(fd, LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void lcdNoAutoscroll(int fd) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  lcdCommand(fd, LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void lcdCreateChar(int fd, uint8_t location, uint8_t charmap[]) {
  int i;
  location &= 0x7; // we only have 8 locations 0-7
  lcdCommand(fd, LCD_SETCGRAMADDR | (location << 3));
  for (i=0; i<8; i++) {
    lcdWrite(fd, charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void lcdCommand(int fd, uint8_t value) {
  lcdSend(fd, value, LOW);
}

inline void lcdWrite(int fd, uint8_t value) {
  lcdSend(fd, value, HIGH);
}

/************ low level data pushing commands **********/

// little wrapper for i/o writes
void  _lcdDigitalWrite(int fd, uint8_t p, uint8_t d) {
  if (_SPIclock != 255) {
    if (d == HIGH)
      _SPIbuff_tx |= (1 << p);
    else 
      _SPIbuff_tx &= ~(1 << p);
      spiRW(fd, 1, &_SPIbuff_tx, &_SPIbuff_rx); //ms
  }
}

// Allows to set the backlight, if the LCD backpack is used
void lcdSetBacklight(int fd, uint8_t status) {
  // check if SPI
  if (_SPIclock != 255) {
    _lcdDigitalWrite(fd, 7, status); // backlight is on pin 7
  }
}

// write either command or data, with automatic 4/8-bit selection
void lcdSend(int fd, uint8_t value, uint8_t mode) {
  _lcdDigitalWrite(fd, _rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    _lcdDigitalWrite(fd, _rw_pin, LOW);
  }
  
  if (_displayfunction & LCD_8BITMODE) {
    lcdWrite8bits(fd, value); 
  } else {
    lcdWrite4bits(fd, value>>4);
    lcdWrite4bits(fd, value);
  }
}

void lcdPulseEnable(int fd) {
  _lcdDigitalWrite(fd, _enable_pin, LOW);
  delayMicroseconds(1);    
  _lcdDigitalWrite(fd, _enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  _lcdDigitalWrite(fd, _enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void lcdWrite4bits(int fd, uint8_t value) {
  int i;
  for (i = 0; i < 4; i++) {
    _lcdDigitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
  }
  lcdPulseEnable(fd);
}

void lcdWrite8bits(int fd, uint8_t value) {
  int i;
  for (i = 0; i < 8; i++) {
    _lcdDigitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
  }
  lcdPulseEnable(fd);
}

void lcdPrint(int fd, const char *s) {
  
  int i;

  for(i = 0; i < strlen(s); i++)
    lcdWrite(fd, s[i]);

}
