#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include <inttypes.h>
//ms #include "Print.h"
//ms #include "Adafruit_MCP23008.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

//ms class LiquidCrystal : public Print {
//ms public:
//ms  LiquidCrystal(uint8_t rs, uint8_t enable,
//ms		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
//ms		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
//ms  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
//ms		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
//ms		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
//ms  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
//ms		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
//ms  LiquidCrystal(uint8_t rs, uint8_t enable,
//ms		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
//ms
//ms  LiquidCrystal(uint8_t i2cAddr);
//ms  LiquidCrystal(uint8_t data, uint8_t clock, uint8_t latch);
  void setup(int fd, uint8_t data, uint8_t clock, uint8_t latch);

  void init(int fd, uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
	    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    
//ms  void begin(int fd, uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  void begin(int fd, uint8_t cols, uint8_t rows, uint8_t charsize);

  void clear(int);
  void home(int);

  void noDisplay(int);
  void display(int);
  void noBlink(int);
  void blink(int);
  void noCursor(int);
  void cursor(int);
  void scrollDisplayLeft(int);
  void scrollDisplayRight(int);
  void leftToRight(int);
  void rightToLeft(int);
  void autoscroll(int);
  void noAutoscroll(int);
  
  // only if using backpack
  void setBacklight(int fd, uint8_t status); 

  void createChar(int, uint8_t, uint8_t[]);
  void setCursor(int, uint8_t, uint8_t); 
//ms #if ARDUINO >= 100
//ms   virtual size_t write(uint8_t);
//ms #else
//ms   virtual void write(uint8_t);
//ms #endif
//ms   void command(uint8_t);
//ms private:
  void command(int, uint8_t);
  void write(int, uint8_t);
  void send(int, uint8_t, uint8_t);
  void write4bits(int, uint8_t);
  void write8bits(int, uint8_t);
  void pulseEnable(int);
  void _digitalWrite(int, uint8_t, uint8_t);
  void _pinMode(uint8_t, uint8_t);

  uint8_t _rs_pin; // LOW: command.  HIGH: character.
  uint8_t _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[8];

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines,_currline;

  uint8_t _SPIclock, _SPIdata, _SPIlatch;
  uint8_t _SPIbuff_tx;
  uint8_t _SPIbuff_rx;

  uint8_t _i2cAddr;
//ms  Adafruit_MCP23008 _i2c;
//ms };

#endif
