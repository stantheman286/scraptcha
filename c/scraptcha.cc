#define BUILDING_NODE_EXTENSION
#include <node.h>

#include<fcntl.h>
#include<string>
extern "C" {
#include "lcd.h"
#include "led.h"
#include "webcam.h"
}

using namespace v8;

/*
function name: lcdTest 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> lcdTest(const Arguments& args) {
	HandleScope scope;

  if ((lcdTest()) < 0) {
		ThrowException(
			Exception::Error(String::New("Unable to execute LCD test program")));
		return scope.Close(Undefined());
	}

  return scope.Close(Undefined());
}

/*
function name: lcdStart 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> lcdStart(const Arguments& args) {
	HandleScope scope;
  int temp;
  Local<Integer> result;

  temp = lcdStart();
  if (temp < 0) {
		ThrowException(
			Exception::Error(String::New("LCD initialization returned invalid descriptor")));
		return scope.Close(Undefined());
	}

  // wrap outputs
  result = Integer::New(temp);
	return scope.Close(result);
}

/*
function name: lcdSetup 
inputs:
	args[0]: fd
  args[1]: data
  args[2]: clock
  args[3]: latch
returns:
	undefined
*/
Handle<Value> lcdSetup(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 4) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();
	int data = args[1]->Int32Value();
	int clock = args[2]->Int32Value();
	int latch = args[3]->Int32Value();

	if ((fd < 0) || (data < 0) || (data > 32) || (clock < 0) || (clock > 32) || (latch < 0) || (latch > 32)) {
		ThrowException(Exception::Error(String::New("Invalid LCD pin settings or descriptor")));
		return scope.Close(Undefined());
	}

  lcdSetup((int32_t)fd, (int32_t)data, (int32_t)clock, (int32_t)latch);

  return scope.Close(Undefined());
}

/*
function name: lcdBegin 
inputs:
	args[0]: fd
  args[1]: columns
  args[2]: lines
  args[3]: dot size
returns:
	undefined
*/
Handle<Value> lcdBegin(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 4) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();
	int cols = args[1]->Int32Value();
	int lines = args[2]->Int32Value();
	int dotsize = args[3]->Int32Value();

	if ((fd < 0) || (cols < 0) || (lines < 0) || (dotsize < 0)) {
		ThrowException(Exception::Error(String::New("Invalid LCD settings or descriptor")));
		return scope.Close(Undefined());
	}

  lcdBegin((int32_t)fd, (int32_t)cols, (int32_t)lines, (int32_t)dotsize);

  return scope.Close(Undefined());
}

/*
function name: lcdClear 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdClear(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdClear((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdHome 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdHome(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdHome((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdSetCursor
inputs:
	args[0]: fd
  args[1]: column
  args[2]: row 
returns:
	undefined
*/
Handle<Value> lcdSetCursor(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 3) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();
	int col = args[1]->Int32Value();
	int row = args[2]->Int32Value();

	if ((fd < 0) || (col < 0) || (row < 0)) {
		ThrowException(Exception::Error(String::New("Invalid LCD location or descriptor")));
		return scope.Close(Undefined());
	}

  lcdSetCursor((int32_t)fd, (int32_t)col, (int32_t)row);

  return scope.Close(Undefined());
}

/*
function name: lcdNoDisplay 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdNoDisplay(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdNoDisplay((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdDisplay
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdDisplay(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdDisplay((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdNoCursor
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdNoCursor(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdNoCursor((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdCursor 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdCursor(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdCursor((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdNoBlink 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdNoBlink(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdNoBlink((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdBlink 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdBlink(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdBlink((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdScrollDisplayLeft 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdScrollDisplayLeft(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdScrollDisplayLeft((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdScrollDisplayRight
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdScrollDisplayRight(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdScrollDisplayRight((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdLeftToRight
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdLeftToRight(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdLeftToRight((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdRightToLeft 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdRightToLeft(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdRightToLeft((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdAutoscroll 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdAutoscroll(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdAutoscroll((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdNoAutoscroll 
inputs:
  args[0]: fd
returns:
	undefined
*/
Handle<Value> lcdNoAutoscroll(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}

  lcdNoAutoscroll((int32_t)fd);

  return scope.Close(Undefined());
}

/*
function name: lcdCreateChar
inputs:
	args[0]: fd
  args[1]: location
  args[2]: character map
returns:
	undefined
*/
//ms: fix, see Array in nodeSPI Handle<Value> createChar(const Arguments& args) {
//ms: fix, see Array in nodeSPI 	HandleScope scope;
//ms: fix, see Array in nodeSPI 
//ms: fix, see Array in nodeSPI 	//Check inputs
//ms: fix, see Array in nodeSPI 	if (args.Length() < 3) {
//ms: fix, see Array in nodeSPI 		ThrowException(
//ms: fix, see Array in nodeSPI 			Exception::TypeError(String::New("Wrong number of arguments")));
//ms: fix, see Array in nodeSPI 		return scope.Close(Undefined());
//ms: fix, see Array in nodeSPI 	}
//ms: fix, see Array in nodeSPI 	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsString()) {
//ms: fix, see Array in nodeSPI 		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
//ms: fix, see Array in nodeSPI 		return scope.Close(Undefined());
//ms: fix, see Array in nodeSPI 	}
//ms: fix, see Array in nodeSPI 
//ms: fix, see Array in nodeSPI   //unpack args
//ms: fix, see Array in nodeSPI 	int fd = args[0]->Int32Value();
//ms: fix, see Array in nodeSPI 	int location = args[1]->Int32Value();
//ms: fix, see Array in nodeSPI 	v8::String::Utf8Value inputString(args[2]->ToString());
//ms: fix, see Array in nodeSPI 	std::string charmap = std::string(*inputString);
//ms: fix, see Array in nodeSPI 
//ms: fix, see Array in nodeSPI 	if ((fd < 0) || (location < 0)) {
//ms: fix, see Array in nodeSPI 		ThrowException(Exception::Error(String::New("Invalid LCD location or descriptor")));
//ms: fix, see Array in nodeSPI 		return scope.Close(Undefined());
//ms: fix, see Array in nodeSPI 	}
//ms: fix, see Array in nodeSPI   //ms: check NULL string
//ms: fix, see Array in nodeSPI 
//ms: fix, see Array in nodeSPI   createChar((int32_t)fd, (int32_t)location, charmap.c_str());
//ms: fix, see Array in nodeSPI 
//ms: fix, see Array in nodeSPI   return scope.Close(Undefined());
//ms: fix, see Array in nodeSPI }

/*
function name: lcdSetBacklight
inputs:
	args[0]: fd
  args[1]: status
returns:
	undefined
*/
Handle<Value> lcdSetBacklight(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 2) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();
	int status = args[1]->Int32Value();

	if ((fd < 0) || (status < 0)) {
		ThrowException(Exception::Error(String::New("Invalid LCD backlight setting or descriptor")));
		return scope.Close(Undefined());
	}

  lcdSetBacklight((int32_t)fd, (int32_t)status);

  return scope.Close(Undefined());
}

/*
function name: lcdPrint
inputs:
	args[0]: fd
  args[1]: string
returns:
	undefined
*/
Handle<Value> lcdPrint(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 2) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int fd = args[0]->Int32Value();
	v8::String::Utf8Value inputString(args[1]->ToString());
	std::string s = std::string(*inputString);

	if (fd < 0) {
		ThrowException(Exception::Error(String::New("Invalid descriptor")));
		return scope.Close(Undefined());
	}
  //ms: check NULL string

  lcdPrint((int32_t)fd, s.c_str());

  return scope.Close(Undefined());
}

/*
function name: ledTest 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> ledTest(const Arguments& args) {
	HandleScope scope;

  ledTest();

  return scope.Close(Undefined());
}

/*
function name: setup_io 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> setup_io(const Arguments& args) {
	HandleScope scope;

  setup_io();

  return scope.Close(Undefined());
}

/*
function name: gpioSetPin 
inputs:
	args[0]: pin number
  args[1]: direction (input/output)
returns:
	undefined
*/
Handle<Value> gpioSetPin(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 2) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int pin = args[0]->Int32Value();
	int dir = args[1]->Int32Value();

	if ((pin < 0) || (pin > 32) || ((dir != GPIO_INPUT) && (dir != GPIO_OUTPUT))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  gpioSetPin((int32_t)pin, (int32_t)dir);

  return scope.Close(Undefined());
}

/*
function name: gpioWrite 
inputs:
	args[0]: pin number
  args[1]: value
returns:
	undefined
*/
Handle<Value> gpioWrite(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 2) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int pin = args[0]->Int32Value();
	int value = args[1]->Int32Value();

	if ((pin < 0) || (pin > 32) || ((value != LOW) && (value != HIGH))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  gpioWrite((int32_t)pin, (int32_t)value);

  return scope.Close(Undefined());
}

/*
function name: shiftOut 
inputs:
	args[0]: anode
  args[1]: bit order (MSB/LSB)
  args[2]: value
returns:
	undefined
*/
Handle<Value> shiftOut(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 3) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int anode = args[0]->Int32Value();
	int bitOrder = args[1]->Int32Value();
	int value = args[2]->Int32Value();

	if (((anode != ANODE0) && (anode != ANODE1) && (anode != ANODE2)) || 
      ((bitOrder != LSBFIRST) && (bitOrder != MSBFIRST)) ||
      (value < 0x00) || (value > 0xFF)){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  shiftOut((int32_t)anode, (int32_t)bitOrder, (int32_t)value);

  return scope.Close(Undefined());
}

/*
function name: ledBarEnable 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> ledBarEnable(const Arguments& args) {
	HandleScope scope;

  ledBarEnable();

  return scope.Close(Undefined());
}

/*
function name: ledBarDisable 
inputs:
	undefined
returns:
	undefined
*/
Handle<Value> ledBarDisable(const Arguments& args) {
	HandleScope scope;

  ledBarDisable();

  return scope.Close(Undefined());
}

/*
function name: ledBlockSet 
inputs:
	args[0]: anode
  args[1]: color (RED/GREEN)
  args[2]: delay
returns:
	undefined
*/
Handle<Value> ledBlockSet(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 3) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int anode = args[0]->Int32Value();
	int color = args[1]->Int32Value();
	int delay = args[2]->Int32Value();

	if (((anode != ANODE0) && (anode != ANODE1) && (anode != ANODE2)) ||
      ((color != RED) && (color != GREEN))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  ledBlockSet((int32_t)anode, (int32_t)color, (int32_t)delay);

  return scope.Close(Undefined());
}

/*
function name: ledScrollSet 
inputs:
  args[0]: delay
returns:
	undefined
*/
Handle<Value> ledScrollSet(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

  //unpack args
	int delay = args[0]->Int32Value();

  ledScrollSet((int32_t)delay);

  return scope.Close(Undefined());
}

/*
function name: takePicture 
inputs:
	args[0]: file name
	args[1]: picture type (CAPTURE or LIVE)
returns:
	undefined
*/
Handle<Value> takePicture(const Arguments& args) {
	HandleScope scope;

	//Check inputs
	if (args.Length() < 2) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsString() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	//unpack args
	v8::String::Utf8Value inputString(args[0]->ToString());
	std::string filename = std::string(*inputString);
//  String::AsciiValue inputString(args[0]->ToString());
//  char *filename = ParseFromString(*inputString, inputString.length());
	int type = args[1]->Int32Value();

	if ((type != CAPTURE) && (type != LIVE)){
		ThrowException(Exception::Error(String::New("Invalid webcam mode")));
		return scope.Close(Undefined());
	}
//	if (filename == Null){
//		ThrowException(Exception::Error(String::New("Invalid file name")));
//		return scope.Close(Undefined());
//	}

	if ((takePicture(filename.c_str(), (int32_t)type)) < 0) {
		ThrowException(
			Exception::Error(String::New("Unable to execute webcam program")));
		return scope.Close(Undefined());
	}

	return scope.Close(Undefined());
}

/*
function name: detectScrap 
inputs:
	args[0]: image name 
returns:
	result of detection, either TRASH/RECYCLING/COMPOST
*/
Handle<Value> detectScrap(const Arguments& args) {
	HandleScope scope;
  int temp;
  Local<Integer> result;

	//Check inputs
	if (args.Length() < 1) {
		ThrowException(
			Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[0]->IsString() ) {
		ThrowException(
			Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	//unwrap inputs
	v8::String::Utf8Value inputString(args[0]->ToString());
	std::string imageName = std::string(*inputString);

  temp = detectScrap(imageName.c_str());

  result = Integer::New(temp);

	return scope.Close(result);
}

void Init(Handle<Object> target) {
	target->Set(String::NewSymbol("lcdTest"),
			FunctionTemplate::New(lcdTest)->GetFunction());
	target->Set(String::NewSymbol("lcdStart"),
			FunctionTemplate::New(lcdStart)->GetFunction());
	target->Set(String::NewSymbol("lcdSetup"),
			FunctionTemplate::New(lcdSetup)->GetFunction());
	target->Set(String::NewSymbol("lcdBegin"),
			FunctionTemplate::New(lcdBegin)->GetFunction());
	target->Set(String::NewSymbol("lcdClear"),
			FunctionTemplate::New(lcdClear)->GetFunction());
	target->Set(String::NewSymbol("lcdHome"),
			FunctionTemplate::New(lcdHome)->GetFunction());
	target->Set(String::NewSymbol("lcdSetCursor"),
			FunctionTemplate::New(lcdSetCursor)->GetFunction());
	target->Set(String::NewSymbol("lcdNoDisplay"),
			FunctionTemplate::New(lcdNoDisplay)->GetFunction());
	target->Set(String::NewSymbol("lcdDisplay"),
			FunctionTemplate::New(lcdDisplay)->GetFunction());
	target->Set(String::NewSymbol("lcdNoCursor"),
			FunctionTemplate::New(lcdNoCursor)->GetFunction());
	target->Set(String::NewSymbol("lcdCursor"),
			FunctionTemplate::New(lcdCursor)->GetFunction());
	target->Set(String::NewSymbol("lcdNoBlink"),
			FunctionTemplate::New(lcdNoBlink)->GetFunction());
	target->Set(String::NewSymbol("lcdBlink"),
			FunctionTemplate::New(lcdBlink)->GetFunction());
	target->Set(String::NewSymbol("lcdScrollDisplayLeft"),
			FunctionTemplate::New(lcdScrollDisplayLeft)->GetFunction());
	target->Set(String::NewSymbol("lcdScrollDisplayRight"),
			FunctionTemplate::New(lcdScrollDisplayRight)->GetFunction());
	target->Set(String::NewSymbol("lcdLeftToRight"),
			FunctionTemplate::New(lcdLeftToRight)->GetFunction());
	target->Set(String::NewSymbol("lcdRightToLeft"),
			FunctionTemplate::New(lcdRightToLeft)->GetFunction());
	target->Set(String::NewSymbol("lcdAutoscroll"),
			FunctionTemplate::New(lcdAutoscroll)->GetFunction());
	target->Set(String::NewSymbol("lcdNoAutoscroll"),
			FunctionTemplate::New(lcdNoAutoscroll)->GetFunction());
//ms 	target->Set(String::NewSymbol("lcdCreateChar"),
//ms 			FunctionTemplate::New(lcdCreateChar)->GetFunction());
	target->Set(String::NewSymbol("lcdSetBacklight"),
			FunctionTemplate::New(lcdSetBacklight)->GetFunction());
	target->Set(String::NewSymbol("lcdPrint"),
			FunctionTemplate::New(lcdPrint)->GetFunction());

	target->Set(String::NewSymbol("ledTest"),
			FunctionTemplate::New(ledTest)->GetFunction());
	target->Set(String::NewSymbol("setup_io"),
			FunctionTemplate::New(setup_io)->GetFunction());
	target->Set(String::NewSymbol("gpioSetPin"),
			FunctionTemplate::New(gpioSetPin)->GetFunction());
	target->Set(String::NewSymbol("gpioWrite"),
			FunctionTemplate::New(gpioWrite)->GetFunction());
	target->Set(String::NewSymbol("shiftOut"),
			FunctionTemplate::New(shiftOut)->GetFunction());
	target->Set(String::NewSymbol("ledBarEnable"),
			FunctionTemplate::New(ledBarEnable)->GetFunction());
	target->Set(String::NewSymbol("ledBarDisable"),
			FunctionTemplate::New(ledBarDisable)->GetFunction());
	target->Set(String::NewSymbol("ledBlockSet"),
			FunctionTemplate::New(ledBlockSet)->GetFunction());
	target->Set(String::NewSymbol("ledScrollSet"),
			FunctionTemplate::New(ledScrollSet)->GetFunction());

	target->Set(String::NewSymbol("takePicture"),
			FunctionTemplate::New(takePicture)->GetFunction());
	target->Set(String::NewSymbol("detectScrap"),
			FunctionTemplate::New(detectScrap)->GetFunction());
}

NODE_MODULE(myScraptcha, Init)

