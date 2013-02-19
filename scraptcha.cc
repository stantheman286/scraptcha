#define BUILDING_NODE_EXTENSION
#include <node.h>

#include<fcntl.h>
//#include<stdio.h> //for debug only
#include<string>
extern "C" {
#include "webcam.h"
}

using namespace v8;

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

	if ((type != CAPTURE) || (type != LIVE)){
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
	target->Set(String::NewSymbol("takePicture"),
			FunctionTemplate::New(takePicture)->GetFunction());
	target->Set(String::NewSymbol("detectScrap"),
			FunctionTemplate::New(detectScrap)->GetFunction());
}

NODE_MODULE(myScraptcha, Init)

