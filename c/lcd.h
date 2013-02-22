#ifndef LCD_H
#define LCD_H

#include <inttypes.h>

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

int lcdTest();
void lcdSetup(int fd, uint8_t data, uint8_t clock, uint8_t latch);
void lcdnit(int fd, uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
void lcdBegin(int fd, uint8_t cols, uint8_t rows, uint8_t charsize);
void lcdClear(int);
void lcdHome(int);
void lcdNoDisplay(int);
void lcdDisplay(int);
void lcdNoBlink(int);
void lcdBlink(int);
void lcdNoCursor(int);
void lcdCursor(int);
void lcdScrollDisplayLeft(int);
void lcdScrollDisplayRight(int);
void lcdLeftToRight(int);
void lcdRightToLeft(int);
void lcdAutoscroll(int);
void lcdNoAutoscroll(int);

// only if using backpack
void lcdSetBacklight(int fd, uint8_t status); 
void lcdCreateChar(int, uint8_t, uint8_t[]);
void lcdSetCursor(int, uint8_t, uint8_t); 
void lcdCommand(int, uint8_t);
void lcdWrite(int, uint8_t);
void lcdSend(int, uint8_t, uint8_t);
void lcdWrite4bits(int, uint8_t);
void lcdWrite8bits(int, uint8_t);
void lcdPulseEnable(int);
void _lcdDigitalWrite(int, uint8_t, uint8_t);
void lcdPrint(int, const char*);
        
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

#endif
