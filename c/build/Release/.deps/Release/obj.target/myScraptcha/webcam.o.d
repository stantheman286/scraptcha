cmd_Release/obj.target/myScraptcha/webcam.o := cc '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/home/pi/.node-gyp/0.8.16/src -I/home/pi/.node-gyp/0.8.16/deps/uv/include -I/home/pi/.node-gyp/0.8.16/deps/v8/include  -fPIC -Wall -pthread -O2 -fno-strict-aliasing -fno-tree-vrp  -MMD -MF ./Release/.deps/Release/obj.target/myScraptcha/webcam.o.d.raw `pkg-config --cflags --libs opencv` -c -o Release/obj.target/myScraptcha/webcam.o ../webcam.c
Release/obj.target/myScraptcha/webcam.o: ../webcam.c \
 /usr/include/opencv/cv.h /usr/include/opencv/highgui.h ../webcam.h
../webcam.c:
/usr/include/opencv/cv.h:
/usr/include/opencv/highgui.h:
../webcam.h:
