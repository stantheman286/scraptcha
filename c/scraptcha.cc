#define BUILDING_NODE_EXTENSION
#include <node.h>

#include<fcntl.h>
#include<string>
extern "C" {
#include "led.h"
#include "webcam.h"
}

using namespace v8;

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

	if (((pin < 32) && (pin > 32)) || ((dir != GPIO_INPUT) && (dir != GPIO_OUTPUT))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  gpioSetPin(pin, dir);

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

	if (((pin < 32) && (pin > 32)) || ((value != LOW) && (value != HIGH))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  gpioSetPin(pin, value);

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

	if (((anode != ANODE0) && (anode != ANODE1) || (anode != ANODE2)) || 
      ((bitOrder != LSBFIRST) && (bitOrder != MSBFIRST)) ||
      ((value != LOW) && (value != HIGH))){
		ThrowException(Exception::Error(String::New("Invalid GPIO settings")));
		return scope.Close(Undefined());
	}

  shiftOut(anode, bitOrder, value);

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

  ledScrollSet(delay);

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

