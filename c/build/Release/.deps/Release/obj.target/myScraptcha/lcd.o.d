cmd_Release/obj.target/myScraptcha/lcd.o := cc '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/matt/.node-gyp/0.8.17/src -I/home/matt/.node-gyp/0.8.17/deps/uv/include -I/home/matt/.node-gyp/0.8.17/deps/v8/include  -fPIC -Wall -pthread -m64 -O2 -fno-strict-aliasing -fno-tree-vrp  -MMD -MF ./Release/.deps/Release/obj.target/myScraptcha/lcd.o.d.raw `pkg-config --cflags --libs opencv` -c -o Release/obj.target/myScraptcha/lcd.o ../lcd.c
Release/obj.target/myScraptcha/lcd.o: ../lcd.c ../wiringPi/wiringPi.h \
 ../nodeSPI/spi.h ../lcd.h
../lcd.c:
../wiringPi/wiringPi.h:
../nodeSPI/spi.h:
../lcd.h:
