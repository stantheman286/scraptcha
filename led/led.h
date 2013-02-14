
#ifndef LED_H
#define LED_H

// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

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

// GPIO pin value macros
#define ANODE0 25
#define ANODE1 24
#define ANODE2 23

#define CLOCK_PIN 22
#define LATCH_PIN 21
#define DATA_PIN 17

// LED bar macros
#define LED0_RED 0xFE
#define LED0_GRN 0xFD
#define LED1_RED 0xFB
#define LED1_GRN 0xF7
#define LED2_RED 0xEF
#define LED2_GRN 0xDF
#define LED3_RED 0xBF
#define LED3_GRN 0x7F

// Prototypes
void setup_io();
void gpioSetPin(uint8_t, uint8_t);
void gpioWrite(uint8_t, uint8_t);
void shiftOut(int, uint8_t, uint8_t);
void ledBarEnable();
void ledBarDisable();

#endif

