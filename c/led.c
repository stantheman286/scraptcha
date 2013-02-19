#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <inttypes.h>
#include "wiringPi/wiringPi.h"
#include "led.h"

//
// LED test code
//
//int main(int argc, char *argv[]) {
void ledTest() {

  int delay;

  // Set delay for all tests
  delay = 250;
  
  // Prepare IO on the Pi
  setup_io();

  // Enable LED bar and reset values
  ledBarEnable();

  // LED block tests
  ledBlockSet(ANODE0, RED, delay);
  ledBlockSet(ANODE1, RED, delay);
  ledBlockSet(ANODE2, RED, delay);
  ledBlockSet(ANODE0, GREEN, delay);
  ledBlockSet(ANODE1, GREEN, delay);
  ledBlockSet(ANODE2, GREEN, delay);

  // Scrolling LED test
  ledScrollSet(delay);

  // When done, disable the LED bar 
  ledBarDisable();

//  return 0;
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
   gpio_map = (unsigned char *)mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
   close(mem_fd); //No need to keep mem_fd open after mmap


   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
} // setup_io

//
// Configure GPIOs as input or output
//
void gpioSetPin(uint8_t pin, uint8_t dir) {

  // Set pin number to given direction
  INP_GPIO(pin);  // Must make pin an input first, even for output
  if (dir == GPIO_OUTPUT)
    OUT_GPIO(pin);
}

// 
// Write a value to the GPIO
//
void gpioWrite(uint8_t pin, uint8_t value) {

  // Need to assert set bit for '1', clear bit for '0'
  if (value == HIGH)
    GPIO_SET = 1<<pin;
  else
    GPIO_CLR = 1<<pin;
}

//
// Shift out values to the cathode pins
//
void shiftOut(int anode, uint8_t bitOrder, uint8_t val)
{
  uint8_t i;

  // Set the correct anode (disable others by setting to input) - TEMP
  if (anode == ANODE0) {

    gpioSetPin(ANODE0, GPIO_OUTPUT);
    gpioSetPin(ANODE1, GPIO_INPUT);
    gpioSetPin(ANODE2, GPIO_INPUT);

    gpioWrite(ANODE0, LOW);

   } else if (anode == ANODE1) {
   
    gpioSetPin(ANODE0, GPIO_INPUT);
    gpioSetPin(ANODE1, GPIO_OUTPUT);
    gpioSetPin(ANODE2, GPIO_INPUT);

    gpioWrite(ANODE1, LOW);
   
   } else {

    gpioSetPin(ANODE0, GPIO_INPUT);
    gpioSetPin(ANODE1, GPIO_INPUT);
    gpioSetPin(ANODE2, GPIO_OUTPUT);

    gpioWrite(ANODE2, LOW);
   
  }

  // Lower latch to start shifting data out
  gpioWrite(LATCH_PIN, LOW);
  
  // Shift one bit per clock
  for (i = 0; i < 8; i++)  {
    if (bitOrder == LSBFIRST)
      gpioWrite(DATA_PIN, !!(val & (1 << i)));
    else  
      gpioWrite(DATA_PIN, !!(val & (1 << (7 - i))));
                              
    gpioWrite(CLOCK_PIN, HIGH);
    gpioWrite(CLOCK_PIN, LOW);    
  }
  
  // Release latch to store value
  gpioWrite(LATCH_PIN, HIGH);

}

// 
// Enable the LED bar
//
void ledBarEnable() {
  
  // Set up GPIO pin directions
  gpioSetPin(ANODE0, GPIO_INPUT); // Disable anodes by setting to input
  gpioSetPin(ANODE1, GPIO_INPUT);
  gpioSetPin(ANODE2, GPIO_INPUT);
  
  gpioSetPin(CLOCK_PIN, GPIO_OUTPUT);
  gpioSetPin(LATCH_PIN, GPIO_OUTPUT);
  gpioSetPin(DATA_PIN, GPIO_OUTPUT);

  // Reset all pin values
  gpioWrite(ANODE0, HIGH);  // Active low
  gpioWrite(ANODE1, HIGH);
  gpioWrite(ANODE2, HIGH);
  
  gpioWrite(LATCH_PIN, HIGH);
  gpioWrite(CLOCK_PIN, HIGH);
  gpioWrite(DATA_PIN, HIGH);

}

// 
// Disable the LED bar
//
void ledBarDisable() {

  // Set all pins to inputs for safety
  gpioSetPin(ANODE0, GPIO_INPUT);
  gpioSetPin(ANODE1, GPIO_INPUT);
  gpioSetPin(ANODE2, GPIO_INPUT);
  
  gpioSetPin(LATCH_PIN, GPIO_INPUT);
  gpioSetPin(CLOCK_PIN, GPIO_INPUT);
  gpioSetPin(DATA_PIN, GPIO_INPUT);

}

//
// Block LED bar test
//
void ledBlockSet(int anode, int color, int d) {
  
  // Output to all LEDs for a given anode based on color
  if (color == RED)
    shiftOut(anode, MSBFIRST, LED0_RED & LED1_RED & LED2_RED & LED3_RED);
  else
    shiftOut(anode, MSBFIRST, LED0_GRN & LED1_GRN & LED2_GRN & LED3_GRN);

  delay(d);

}

//
// Scrolling LED bar test
//
void ledScrollSet(int d) {

  // Run through all the red LEDs
  shiftOut(ANODE0, MSBFIRST, LED0_RED);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED1_RED);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED2_RED);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED3_RED);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED0_RED);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED1_RED);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED2_RED);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED3_RED);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED0_RED);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED1_RED);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED2_RED);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED3_RED);
  delay(d);

  // Run through all the green LEDs
  shiftOut(ANODE0, MSBFIRST, LED0_GRN);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED1_GRN);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED2_GRN);
  delay(d);
  shiftOut(ANODE0, MSBFIRST, LED3_GRN);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED0_GRN);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED1_GRN);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED2_GRN);
  delay(d);
  shiftOut(ANODE1, MSBFIRST, LED3_GRN);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED0_GRN);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED1_GRN);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED2_GRN);
  delay(d);
  shiftOut(ANODE2, MSBFIRST, LED3_GRN);
  delay(d);

}

