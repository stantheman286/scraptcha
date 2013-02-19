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
  
  // set up the LCD's number of rows and columns: 
  begin(fd, 16, 2, LCD_5x8DOTS);
  // Print a message to the LCD.
  lcdPrint(fd, "hello, world!");
 
  // Kill text and backlight if not using
//  if ((argc == 2) && (strcmp(argv[1], "--off") == 0)) {
//    noDisplay(fd);
//    setBacklight(fd, LOW);
//  }

//  while(1)
//    loop(fd);
  
  return 0;

}

void setup(int fd, uint8_t data, uint8_t clock, uint8_t latch ) {

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

  // we can't begin() yet :(
  begin(fd, 16, 1, LCD_5x8DOTS);
}


void init(int fd, uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
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
  
  begin(fd, 16, 1, LCD_5x8DOTS);  
}

void begin(int fd, uint8_t cols, uint8_t lines, uint8_t dotsize) {
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
  _digitalWrite(fd, _rs_pin, LOW);
  _digitalWrite(fd, _enable_pin, LOW);
  if (_rw_pin != 255) { 
    _digitalWrite(fd, _rw_pin, LOW);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (! (_displayfunction & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(fd, 0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    write4bits(fd, 0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    write4bits(fd, 0x03); 
    delayMicroseconds(150);

    // finally, set to 8-bit interface
    write4bits(fd, 0x02); 
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    command(fd, LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(4500);  // wait more than 4.1ms

    // second try
    command(fd, LCD_FUNCTIONSET | _displayfunction);
    delayMicroseconds(150);

    // third go
    command(fd, LCD_FUNCTIONSET | _displayfunction);
  }

  // finally, set # lines, font size, etc.
  command(fd, LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
  display(fd);

  // clear it off
  clear(fd);

  // Initialize to default text direction (for romance languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  command(fd, LCD_ENTRYMODESET | _displaymode);

}

/********** high level commands, for the user! */
void clear(int fd)
{
  command(fd, LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void home(int fd)
{
  command(fd, LCD_RETURNHOME);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void setCursor(int fd, uint8_t col, uint8_t row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row > _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }
  
  command(fd, LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void noDisplay(int fd) {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void display(int fd) {
  _displaycontrol |= LCD_DISPLAYON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void noCursor(int fd) {
  _displaycontrol &= ~LCD_CURSORON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor(int fd) {
  _displaycontrol |= LCD_CURSORON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void noBlink(int fd) {
  _displaycontrol &= ~LCD_BLINKON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink(int fd) {
  _displaycontrol |= LCD_BLINKON;
  command(fd, LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(int fd) {
  command(fd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(int fd) {
  command(fd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(int fd) {
  _displaymode |= LCD_ENTRYLEFT;
  command(fd, LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(int fd) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(fd, LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(int fd) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(fd, LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(int fd) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(fd, LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(int fd, uint8_t location, uint8_t charmap[]) {
  int i;
  location &= 0x7; // we only have 8 locations 0-7
  command(fd, LCD_SETCGRAMADDR | (location << 3));
  for (i=0; i<8; i++) {
    lcdWrite(fd, charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void command(int fd, uint8_t value) {
  lcdSend(fd, value, LOW);
}

inline void lcdWrite(int fd, uint8_t value) {
  lcdSend(fd, value, HIGH);
}

/************ low level data pushing commands **********/

// little wrapper for i/o writes
void  _digitalWrite(int fd, uint8_t p, uint8_t d) {
  if (_SPIclock != 255) {
    if (d == HIGH)
      _SPIbuff_tx |= (1 << p);
    else 
      _SPIbuff_tx &= ~(1 << p);
      spiRW(fd, 1, &_SPIbuff_tx, &_SPIbuff_rx); //ms
  }
}

// Allows to set the backlight, if the LCD backpack is used
void setBacklight(int fd, uint8_t status) {
  // check if SPI
  if (_SPIclock != 255) {
    _digitalWrite(fd, 7, status); // backlight is on pin 7
  }
}

// write either command or data, with automatic 4/8-bit selection
void lcdSend(int fd, uint8_t value, uint8_t mode) {
  _digitalWrite(fd, _rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    _digitalWrite(fd, _rw_pin, LOW);
  }
  
  if (_displayfunction & LCD_8BITMODE) {
    write8bits(fd, value); 
  } else {
    write4bits(fd, value>>4);
    write4bits(fd, value);
  }
}

void pulseEnable(int fd) {
  _digitalWrite(fd, _enable_pin, LOW);
  delayMicroseconds(1);    
  _digitalWrite(fd, _enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  _digitalWrite(fd, _enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void write4bits(int fd, uint8_t value) {
  int i;
  for (i = 0; i < 4; i++) {
    _digitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable(fd);
}

void write8bits(int fd, uint8_t value) {
  int i;
  for (i = 0; i < 8; i++) {
    _digitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable(fd);
}

void lcdPrint(int fd, const char *s) {
  
  int i;

  for(i = 0; i < strlen(s); i++)
    lcdWrite(fd, s[i]);

}
