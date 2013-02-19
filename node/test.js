var scraptcha = require('../c/build/Release/myScraptcha');

// Constants
var LOW = 0;
var HIGH = 1;

var LSBFIRST = 0;
var MSBFIRST = 1;

var GPIO_OUTPUT = 0;
var GPIO_INPUT = 1;

var ANODE0 = 25;
var ANODE1 = 24;
var ANODE2 = 23;

var CLOCK_PIN = 22
var LATCH_PIN = 21
var DATA_PIN = 17

var LED0_RED = 0xFE;
var LED0_GRN = 0xFD;
var LED1_RED = 0xFB;
var LED1_GRN = 0xF7;
var LED2_RED = 0xEF;
var LED2_GRN = 0xDF;
var LED3_RED = 0xBF;
var LED3_GRN = 0x7F;

var RED = 0;
var GREEN = 1;

var TRASH = 0;
var RECYCLING = 1;
var COMPOST = 2;

var CAPTURE = 0;
var LIVE = 1;

// Variables
var delay;
var filename = 'test.jpg';
var type;

// LED test
delay = 250;

scraptcha.setup_io;

scraptcha.ledBarEnable;

scraptcha.ledBlockSet(ANODE0, RED, delay);
scraptcha.ledBlockSet(ANODE1, RED, delay);
scraptcha.ledBlockSet(ANODE2, RED, delay);
scraptcha.ledBlockSet(ANODE0, GREEN, delay);
scraptcha.ledBlockSet(ANODE1, GREEN, delay);
scraptcha.ledBlockSet(ANODE2, GREEN, delay);

scraptcha.ledScrollSet(delay);

scraptcha.ledBarDisable;


// Webcam test
// scraptcha.takePicture(filename, CAPTURE);
// type = scraptcha.detectScrap(filename);
// 
// switch(type) {
//   case TRASH: console.log('TRASH!!!\n'); break;
//   case RECYCLING: console.log('RECYCLING!!!\n'); break;
//   case COMPOST: console.log('COMPOST!!!\n'); break;
//   default: break;
// }

