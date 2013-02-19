cmd_Release/obj.target/myScraptcha/wiringPi/wiringPi.o := cc '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/pi/.node-gyp/0.8.16/src -I/home/pi/.node-gyp/0.8.16/deps/uv/include -I/home/pi/.node-gyp/0.8.16/deps/v8/include  -fPIC -Wall -pthread -O2 -fno-strict-aliasing -fno-tree-vrp  -MMD -MF ./Release/.deps/Release/obj.target/myScraptcha/wiringPi/wiringPi.o.d.raw `pkg-config --cflags --libs opencv` -c -o Release/obj.target/myScraptcha/wiringPi/wiringPi.o ../wiringPi/wiringPi.c
Release/obj.target/myScraptcha/wiringPi/wiringPi.o: \
 ../wiringPi/wiringPi.c ../wiringPi/wiringPi.h
../wiringPi/wiringPi.c:
../wiringPi/wiringPi.h:
