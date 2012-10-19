
CXX=g++
LIBS=-lGLESv2
CXXFLAGS=-Wall
INC_DIRS=

shader.o: shader.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(?) -o $(@)

clean:
	rm -rf *~
	rm -rf *.o


.PHONY: clean
