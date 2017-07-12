GCC=g++
LIBS=-lmingw32 -lSDL2main -lSDL2 -lglew32 -lOpenGL32
LIBS_LINUX=-lSDL2main -lSDL2 -lGLEW -lGL
FLAGS=-std=gnu++11 -Wall -O2
OBJ_FILES= ../../obj/IDevice.o\
	  ../../obj/IObjectHandle.o\
	  ../../obj/Buffer.o\
	  ../../obj/VertexArray.o\
	  ../../obj/BufferTypes.o\
	  ../../obj/GLDevice.o\
	  ../../obj/main.o

all:
	$(GCC) ../../src/main.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/main.o
	$(GCC) ../../src/IObjectHandle.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/IObjectHandle.o
	$(GCC) ../../src/Buffer.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/Buffer.o
	$(GCC) ../../src/VertexArray.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/VertexArray.o
	$(GCC) ../../src/IDevice.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/IDevice.o
	$(GCC) ../../src/BufferTypes.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/BufferTypes.o
	$(GCC) ../../src/GLDevice.cpp $(LIBS_LINUX) $(FLAGS) -c -o ../../obj/GLDevice.o
link:
	$(GCC) $(OBJ_FILES) $(LIBS_LINUX) $(FLAGS) -o ../../bin/Game_linux
clean:
	rm ../../obj/*.o
exec:
	../../bin/Game_linux
