cmd_Release/obj.target/myScraptcha/led.o := cc '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/matt/.node-gyp/0.8.17/src -I/home/matt/.node-gyp/0.8.17/deps/uv/include -I/home/matt/.node-gyp/0.8.17/deps/v8/include  -fPIC -Wall -pthread -m64 -O2 -fno-strict-aliasing -fno-tree-vrp  -MMD -MF ./Release/.deps/Release/obj.target/myScraptcha/led.o.d.raw `pkg-config --cflags --libs opencv` -c -o Release/obj.target/myScraptcha/led.o ../led.c
Release/obj.target/myScraptcha/led.o: ../led.c ../led.h
../led.c:
../led.h:
