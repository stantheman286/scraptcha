var scraptcha = require('../build/Release/myScraptcha');

// Constants
var TRASH = 0;
var RECYCLING = 1;
var COMPOST = 2;

var CAPTURE = 0;
var LIVE = 1;

// Variables
var filename = 'test.jpg';
var type;

scraptcha.takePicture(filename, CAPTURE);
type = scraptcha.detectScrap(filename);

switch(type) {
  case TRASH: console.log('TRASH!!!\n'); break;
  case RECYCLING: console.log('RECYCLING!!!\n'); break;
  case COMPOST: console.log('COMPOST!!!\n'); break;
  default: break;
}

