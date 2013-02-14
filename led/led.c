// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <inttypes.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#define LOW     0
#define HIGH     1

#define LSBFIRST     0
#define MSBFIRST     1

#define GPIO_OUTPUT     0
#define GPIO_INPUT     1

int  mem_fd;
char *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

void gpioSetPin(uint8_t pin, uint8_t dir) {

  // Set pin number to given direction
  INP_GPIO(pin);  // Must make pin an input first, even for output
  if (dir == GPIO_OUTPUT)
    OUT_GPIO(pin);
}

void gpioWrite(uint8_t pin, uint8_t value) {

  // Need to assert set bit for '1', clear bit for '0'
  if (value == HIGH)
    GPIO_SET = 1<<pin;
  else
    GPIO_CLR = 1<<pin;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
  uint8_t i;

  for (i = 0; i < 8; i++)  {
    if (bitOrder == LSBFIRST)
      gpioWrite(dataPin, !!(val & (1 << i)));
    else  
      gpioWrite(dataPin, !!(val & (1 << (7 - i))));
                              
    gpioWrite(clockPin, HIGH);
    gpioWrite(clockPin, LOW);    
  }

}

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = (char *)mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
   close(mem_fd); //No need to keep mem_fd open after mmap


   if ((long)gpio_map < 0) {
      printf("mmap error %d\n", (int)gpio_map);
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
} // setup_io

int main(int argc, char *argv[]) {

  int g, rep, numberToDisplay;
  int latchPin, dataPin, clockPin;

  // Prepare IO on the Pi
  setup_io();

  // Set up GPIO pins

  // Write test code
  
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    gpioWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
    
    //take the latch pin high so the LEDs will light up:
    gpioWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
  
  // When done, set all pins to input for safety

  return 0;

}

