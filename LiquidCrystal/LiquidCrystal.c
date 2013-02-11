#include "LiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "wiringPi/wiringPi.h"
#include "nodeSPI/spi.h"

//#if ARDUINO >= 100
// #include "Arduino.h"
//#else
// #include "WProgram.h"
//#endif

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
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

//ms LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
//ms 			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
//ms 			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
//ms {
//ms   init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
//ms }
//ms 
//ms LiquidCrystal(uint8_t rs, uint8_t enable,
//ms 			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
//ms 			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
//ms {
//ms   init(0, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
//ms }
//ms 
//ms LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
//ms 			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
//ms {
//ms   init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
//ms }
//ms 
//ms LiquidCrystal(uint8_t rs,  uint8_t enable,
//ms 			     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
//ms {
//ms   init(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
//ms }
//ms 
//ms LiquidCrystal(uint8_t i2caddr) {
//ms   _i2cAddr = i2caddr;
//ms 
//ms   _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
//ms   
//ms   // the I/O expander pinout
//ms   _rs_pin = 1;
//ms   _rw_pin = 255;
//ms   _enable_pin = 2;
//ms   _data_pins[0] = 3;  // really d4
//ms   _data_pins[1] = 4;  // really d5
//ms   _data_pins[2] = 5;  // really d6
//ms   _data_pins[3] = 6;  // really d7
//ms   
//ms   // we can't begin() yet :(
//ms }


//ms LiquidCrystal(uint8_t data, uint8_t clock, uint8_t latch ) {
void setup(int fd, uint8_t data, uint8_t clock, uint8_t latch ) {
  _i2cAddr = 255;

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

//ms  pinMode(_SPIdata, OUTPUT);
//ms  pinMode(_SPIclock, OUTPUT);
//ms  pinMode(_SPIlatch, OUTPUT);
//ms  _SPIbuff = 0;
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

  _i2cAddr = 255;
  _SPIclock = _SPIdata = _SPIlatch = 255;

//ms  pinMode(_rs_pin, OUTPUT);
//ms  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
//ms  if (_rw_pin != 255) { 
//ms    pinMode(_rw_pin, OUTPUT);
//ms  }
//ms  pinMode(_enable_pin, OUTPUT);
  
  if (fourbitmode)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
  begin(fd, 16, 1, LCD_5x8DOTS);  
}

void begin(int fd, uint8_t cols, uint8_t lines, uint8_t dotsize) {
  // check if i2c
  if (_i2cAddr != 255) {
//ms    _i2c.begin(_i2cAddr);

//ms    _i2c.pinMode(7, OUTPUT); // backlight
//ms    _i2c.digitalWrite(7, HIGH); // backlight

//ms    for (uint8_t i=0; i<4; i++)
//ms      _pinMode(_data_pins[i], OUTPUT);

//ms    _i2c.pinMode(_rs_pin, OUTPUT);
//ms    _i2c.pinMode(_enable_pin, OUTPUT);
  } else if (_SPIclock != 255) {
//ms    _SPIbuff = 0x80; // backlight
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
    write(fd, charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void command(int fd, uint8_t value) {
  send(fd, value, LOW);
}

// #if ARDUINO >= 100
// inline size_t write(uint8_t value) {
//   send(value, HIGH);
//   return 1;
// }
// #else
inline void write(int fd, uint8_t value) {
  send(fd, value, HIGH);
}
// #endif

/************ low level data pushing commands **********/

// little wrapper for i/o writes
void  _digitalWrite(int fd, uint8_t p, uint8_t d) {
  if (_i2cAddr != 255) {
    // an i2c command
//ms    _i2c.digitalWrite(p, d);
  } else if (_SPIclock != 255) {
    if (d == HIGH)
      _SPIbuff_tx |= (1 << p);
    else 
      _SPIbuff_tx &= ~(1 << p);

//ms    digitalWrite(_SPIlatch, LOW);
//ms    shiftOut(_SPIdata, _SPIclock, MSBFIRST,_SPIbuff);
//ms    digitalWrite(_SPIlatch, HIGH);

      spiRW(fd, 1, &_SPIbuff_tx, &_SPIbuff_rx);

  } else {
    // straightup IO
//ms    digitalWrite(p, d);
  }
}

// Allows to set the backlight, if the LCD backpack is used
void setBacklight(int fd, uint8_t status) {
  // check if i2c or SPI
  if ((_i2cAddr != 255) || (_SPIclock != 255)) {
    _digitalWrite(fd, 7, status); // backlight is on pin 7
  }
}

// little wrapper for i/o directions
void  _pinMode(uint8_t p, uint8_t d) {
  if (_i2cAddr != 255) {
    // an i2c command
//ms    _i2c.pinMode(p, d);
  } else if (_SPIclock != 255) {
    // nothing!
  } else {
    // straightup IO
//ms    pinMode(p, d);
  }
}

// write either command or data, with automatic 4/8-bit selection
void send(int fd, uint8_t value, uint8_t mode) {
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
  if (_i2cAddr != 255) {
    uint8_t out = 0;

//ms    out = _i2c.readGPIO();


    // speed up for i2c since its sluggish
    for (i = 0; i < 4; i++) {
//ms      out &= ~_BV(_data_pins[i]);
      out |= ((value >> i) & 0x1) << _data_pins[i];
    }

    // make sure enable is low
//ms    out &= ~ _BV(_enable_pin);

//ms    _i2c.writeGPIO(out);

    // pulse enable
    delayMicroseconds(1);
//ms    out |= _BV(_enable_pin);
//ms    _i2c.writeGPIO(out);
    delayMicroseconds(1);
//ms    out &= ~_BV(_enable_pin);
//ms    _i2c.writeGPIO(out);   
    delayMicroseconds(100);
  } else {
    for (i = 0; i < 4; i++) {
//ms      _pinMode(_data_pins[i], OUTPUT);
      _digitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
    }
    pulseEnable(fd);
  }
}

void write8bits(int fd, uint8_t value) {
  int i;
  for (i = 0; i < 8; i++) {
//ms    _pinMode(_data_pins[i], OUTPUT);
    _digitalWrite(fd, _data_pins[i], (value >> i) & 0x01);
  }
  
  pulseEnable(fd);
}
