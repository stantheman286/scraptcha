cmd_Release/obj.target/myScraptcha.node := flock ./Release/linker.lock g++ -shared -pthread -rdynamic `pkg-config --cflags --libs opencv` -Wl,-soname=myScraptcha.node -o Release/obj.target/myScraptcha.node -Wl,--start-group Release/obj.target/myScraptcha/webcam.o Release/obj.target/myScraptcha/wiringPi/wiringPi.o Release/obj.target/myScraptcha/led.o Release/obj.target/myScraptcha/scraptcha.o -Wl,--end-group 
