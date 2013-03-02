cmd_Release/obj.target/myScraptcha/led.o := cc '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/root/.node-gyp/0.8.16/src -I/root/.node-gyp/0.8.16/deps/uv/include -I/root/.node-gyp/0.8.16/deps/v8/include  -fPIC -Wall -pthread -O2 -fno-strict-aliasing -fno-tree-vrp  -MMD -MF ./Release/.deps/Release/obj.target/myScraptcha/led.o.d.raw `pkg-config --cflags --libs opencv` -c -o Release/obj.target/myScraptcha/led.o ../led.c
Release/obj.target/myScraptcha/led.o: ../led.c ../wiringPi/wiringPi.h \
 ../led.h
../led.c:
../wiringPi/wiringPi.h:
../led.h:
