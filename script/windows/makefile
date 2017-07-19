GCC=g++
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lglew32 -lOpenGL32
LIBS_LINUX=-lSDL2main -lSDL2 -lGLEW -lGL
FLAGS=-std=gnu++14 -Wall -O2
OBJ_FILES= ../../obj/IDevice.o\
	  ../../obj/IObjectHandle.o\
	  ../../obj/Buffer.o\
	  ../../obj/VertexArray.o\
	  ../../obj/BufferTypes.o\
	  ../../obj/GLDevice.o\
	  ../../obj/Shader.o\
	  ../../obj/IShaderSet.o\
	  ../../obj/DefaultShader.o\
	  ../../obj/TestShader.o\
	  ../../obj/PostProcessorShader.o\
	  ../../obj/Renderbuffer.o\
	  ../../obj/Framebuffer.o\
	  ../../obj/ShaderProgram.o\
	  ../../obj/SpriteBatcher.o\
	  ../../obj/ShaderUniform.o\
	  ../../obj/Texture.o\
	  ../../obj/Bitmap.o\
	  ../../obj/BitmapUtil.o\
	  ../../obj/sdl_surface_load_image_wrapper.o\
	  ../../obj/vectors.o\
	  ../../obj/main.o
all:
	$(GCC) ../../src/main.cpp $(LIBS) $(FLAGS) -c -o ../../obj/main.o
	$(GCC) ../../src/IObjectHandle.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IObjectHandle.o
	$(GCC) ../../src/Buffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Buffer.o
	$(GCC) ../../src/VertexArray.cpp $(LIBS) $(FLAGS) -c -o ../../obj/VertexArray.o
	$(GCC) ../../src/IDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IDevice.o
	$(GCC) ../../src/BufferTypes.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BufferTypes.o
	$(GCC) ../../src/GLDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/GLDevice.o
	$(GCC) ../../src/Shader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Shader.o
	$(GCC) ../../src/IShaderSet.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IShaderSet.o
	$(GCC) ../../src/DefaultShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/DefaultShader.o
	$(GCC) ../../src/TestShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TestShader.o
	$(GCC) ../../src/PostProcessorShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/PostProcessorShader.o
	$(GCC) ../../src/ShaderProgram.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderProgram.o
	$(GCC) ../../src/vectors.cpp $(LIBS) $(FLAGS) -c -o ../../obj/vectors.o
	$(GCC) ../../src/ShaderUniform.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderUniform.o
	$(GCC) ../../src/SpriteBatcher.cpp $(LIBS) $(FLAGS) -c -o ../../obj/SpriteBatcher.o
	$(GCC) ../../src/Bitmap.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Bitmap.o
	$(GCC) ../../src/Renderbuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Renderbuffer.o
	$(GCC) ../../src/Framebuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Framebuffer.o
	$(GCC) ../../src/BitmapUtil.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BitmapUtil.o
	$(GCC) ../../src/sdl_surface_load_image_wrapper.cpp $(LIBS) $(FLAGS) -c -o ../../obj/sdl_surface_load_image_wrapper.o
	$(GCC) ../../src/Texture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Texture.o
link:
	$(GCC) $(OBJ_FILES) $(LIBS) $(FLAGS) -o ../../bin/Game.exe
clean:
	rm ../../obj/*.o
exec:
	../../bin/Game.exe
