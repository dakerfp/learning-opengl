
CC=gcc
CXX=g++
CFLAGS=-Wall
# INCLUDE=-I/usr/includes/EGL
# LIBS=`pkg-config --cflags --libs egl` `pkg-config --cflags --libs gles2`

LIBS=-lGLESv2 -lEGL -lX11


egl: main.c
	$(CXX) $(CFLAGS) $(LIBS) $(?) -o $(@)

clean:
	rm -rf egl
	rm -rf *~

.PHONY: clean
