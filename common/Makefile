
CXX=g++
LIBS=-lGLESv2 -lEGL
CXXFLAGS=-Wall
INC_DIRS=


all: shader.o program.o rendercontext.o windowrendercontext.o

shader.o: shader.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(?) -o $(@)

program.o: program.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(?) -o $(@)

rendercontext.o: rendercontext.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(?) -o $(@)

windowrendercontext.o: windowrendercontext.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $(?) -o $(@)

clean:
	rm -rf *~
	rm -rf *.o


.PHONY: clean
