GCC=g++
LIBS=-lSDL2main -lSDL2 -lSDL2_image -lGLEW -lGL
FLAGS=-std=gnu++14 -Wall -O2
OBJ_FILES= ../../obj/IDevice.o\
	  ../../obj/IObjectHandle.o\
	  ../../obj/Buffer.o\
	  ../../obj/VertexArray.o\
	  ../../obj/BufferTypes.o\
	  ../../obj/GLDevice.o\
	  ../../obj/Shader.o\
	  ../../obj/ShaderProgram.o\
	  ../../obj/ShaderUniform.o\
	  ../../obj/Texture.o\
	  ../../obj/Bitmap.o\
	  ../../obj/RandomNumberGenerator.o\
	  ../../obj/ParticleGenerator.o\
	  ../../obj/ParticleRenderer.o\
	  ../../obj/BitmapUtil.o\
	  ../../obj/Framebuffer.o\
	  ../../obj/Renderbuffer.o\
	  ../../obj/Postprocessor.o\
	  ../../obj/ImageTexture.o\
	  ../../obj/TestShader.o\
	  ../../obj/SpriteBatcher.o\
	  ../../obj/DefaultShader.o\
	  ../../obj/IShaderSet.o\
	  ../../obj/PostProcessorShader.o\
	  ../../obj/sdl_surface_load_image_wrapper.o\
	  ../../obj/vectors.o\
	  ../../obj/LightShader.o\
	  ../../obj/ClockTimer.o\
	  ../../obj/main.o
all:
	$(GCC) ../../src/main.cpp $(LIBS) $(FLAGS) -c -o ../../obj/main.o 2> ../../logs/main.log
	$(GCC) ../../src/IObjectHandle.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IObjectHandle.o 2> ../../logs/objHandle.log
	$(GCC) ../../src/LightShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/LightShader.o 2> ../../logs/lightShader.log
	$(GCC) ../../src/Buffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Buffer.o 2> ../../logs/buffer.log
	$(GCC) ../../src/VertexArray.cpp $(LIBS) $(FLAGS) -c -o ../../obj/VertexArray.o 2> ../../logs/vertexarray.log
	$(GCC) ../../src/IDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IDevice.o 2> ../../logs/idevice.log
	$(GCC) ../../src/BufferTypes.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BufferTypes.o 2> ../../logs/buffertypes.log
	$(GCC) ../../src/GLDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/GLDevice.o 2> ../../logs/gldevice.log
	$(GCC) ../../src/Shader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Shader.o 2> ../../logs/shader.log
	$(GCC) ../../src/IShaderSet.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IShaderSet.o 2> ../../logs/ishaderset.log
	$(GCC) ../../src/DefaultShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/DefaultShader.o 2> ../../logs/defaultshader.log
	$(GCC) ../../src/TestShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TestShader.o 2> ../../logs/testshader.log
	$(GCC) ../../src/PostProcessorShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/PostProcessorShader.o 2> ../../logs/postprocessorshader.log
	$(GCC) ../../src/ShaderProgram.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderProgram.o 2> ../../logs/shaderprogram.log
	$(GCC) ../../src/vectors.cpp $(LIBS) $(FLAGS) -c -o ../../obj/vectors.o 2> ../../logs/vectors.log
	$(GCC) ../../src/ShaderUniform.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderUniform.o 2> ../../logs/shaderuniform.log
	$(GCC) ../../src/SpriteBatcher.cpp $(LIBS) $(FLAGS) -c -o ../../obj/SpriteBatcher.o 2> ../../logs/spritebatcher.log
	$(GCC) ../../src/Bitmap.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Bitmap.o 2> ../../logs/bitmap.log
	$(GCC) ../../src/Renderbuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Renderbuffer.o 2> ../../logs/renderbuffer.log
	$(GCC) ../../src/Framebuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Framebuffer.o 2> ../../logs/framebuffer.log
	$(GCC) ../../src/Postprocessor.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Postprocessor.o 2> ../../logs/postprocessor.log
	$(GCC) ../../src/ImageTexture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ImageTexture.o 2> ../../logs/imagetexture.log
	$(GCC) ../../src/RandomNumberGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/RandomNumberGenerator.o 2> ../../logs/rng.log
	$(GCC) ../../src/BitmapUtil.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BitmapUtil.o 2> ../../logs/bitmaputil.log
	$(GCC) ../../src/sdl_surface_load_image_wrapper.cpp $(LIBS) $(FLAGS) -c -o ../../obj/sdl_surface_load_image_wrapper.o 2> ../../logs/imagesurface.log
	$(GCC) ../../src/Texture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Texture.o 2> ../../logs/texture.log
	$(GCC) ../../src/ParticleGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleGenerator.o 2> ../../logs/particlegen.log
	$(GCC) ../../src/ParticleRenderer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleRenderer.o 2> ../../logs/particlerender.log
	$(GCC) ../../src/ClockTimer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ClockTimer.o 2> ../../logs/clocktimer.log
link:
	$(GCC) $(OBJ_FILES) $(LIBS) $(FLAGS) -o ../../bin/Game_linux 2> ../../logs/linker.log
clean:
	rm ../../obj/*.o
exec:
	../../bin/Game_linux
