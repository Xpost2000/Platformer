GCC=g++
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lglew32 -lOpenGL32 -lboost_random-mgw51-1_60
LIBS_LINUX=-lSDL2main -lSDL2 -lGLEW -lGL
FLAGS=-std=gnu++14 -Wall -O2
OBJ_FILES= ../../obj/IDevice.o\
	  ../../obj/IObjectHandle.o\
	  ../../obj/LightShader.o\
	  ../../obj/Buffer.o\
	  ../../obj/ParticleGenerator.o\
	  ../../obj/ParticleRenderer.o\
	  ../../obj/VertexArray.o\
	  ../../obj/BufferTypes.o\
	  ../../obj/GLDevice.o\
	  ../../obj/ClockTimer.o\
	  ../../obj/Shader.o\
	  ../../obj/Player.o\
	  ../../obj/BasicEnemy.o\
	  ../../obj/JumpingEnemy.o\
	  ../../obj/IShaderSet.o\
	  ../../obj/ImageTexture.o\
	  ../../obj/DefaultShader.o\
	  ../../obj/TestShader.o\
	  ../../obj/PostProcessorShader.o\
	  ../../obj/PostProcessor.o\
	  ../../obj/Renderbuffer.o\
	  ../../obj/RandomNumberGenerator.o\
	  ../../obj/Framebuffer.o\
	  ../../obj/ShaderProgram.o\
	  ../../obj/SpriteBatcher.o\
	  ../../obj/ShaderUniform.o\
	  ../../obj/Texture.o\
	  ../../obj/Bitmap.o\
	  ../../obj/Block.o\
	  ../../obj/Entity.o\
	  ../../obj/BitmapUtil.o\
	  ../../obj/sdl_surface_load_image_wrapper.o\
	  ../../obj/vectors.o\
	  ../../obj/Game.o\
	  ../../obj/main.o
all:
	$(GCC) ../../src/main.cpp $(LIBS) $(FLAGS) -c -o ../../obj/main.o 2> ../../logs/win/main.log
	$(GCC) ../../src/IObjectHandle.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IObjectHandle.o 2> ../../logs/win/objHandle.log
	$(GCC) ../../src/LightShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/LightShader.o 2> ../../logs/win/lightShader.log
	$(GCC) ../../src/Buffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Buffer.o 2> ../../logs/win/buffer.log
	$(GCC) ../../src/VertexArray.cpp $(LIBS) $(FLAGS) -c -o ../../obj/VertexArray.o 2> ../../logs/win/vertexarray.log
	$(GCC) ../../src/IDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IDevice.o 2> ../../logs/win/idevice.log
	$(GCC) ../../src/BufferTypes.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BufferTypes.o 2> ../../logs/win/buffertypes.log
	$(GCC) ../../src/GLDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/GLDevice.o 2> ../../logs/win/gldevice.log
	$(GCC) ../../src/Shader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Shader.o 2> ../../logs/win/shader.log
	$(GCC) ../../src/IShaderSet.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IShaderSet.o 2> ../../logs/win/ishaderset.log
	$(GCC) ../../src/DefaultShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/DefaultShader.o 2> ../../logs/win/defaultshader.log
	$(GCC) ../../src/TestShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TestShader.o 2> ../../logs/win/testshader.log
	$(GCC) ../../src/PostProcessorShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/PostProcessorShader.o 2> ../../logs/win/postprocessorshader.log
	$(GCC) ../../src/ShaderProgram.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderProgram.o 2> ../../logs/win/shaderprogram.log
	$(GCC) ../../src/vectors.cpp $(LIBS) $(FLAGS) -c -o ../../obj/vectors.o 2> ../../logs/win/vectors.log
	$(GCC) ../../src/ShaderUniform.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderUniform.o 2> ../../logs/win/shaderuniform.log
	$(GCC) ../../src/SpriteBatcher.cpp $(LIBS) $(FLAGS) -c -o ../../obj/SpriteBatcher.o 2> ../../logs/win/spritebatcher.log
	$(GCC) ../../src/Bitmap.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Bitmap.o 2> ../../logs/win/bitmap.log
	$(GCC) ../../src/Renderbuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Renderbuffer.o 2> ../../logs/win/renderbuffer.log
	$(GCC) ../../src/Framebuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Framebuffer.o 2> ../../logs/win/framebuffer.log
	$(GCC) ../../src/Postprocessor.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Postprocessor.o 2> ../../logs/win/postprocessor.log
	$(GCC) ../../src/ImageTexture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ImageTexture.o 2> ../../logs/win/imagetexture.log
	$(GCC) ../../src/RandomNumberGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/RandomNumberGenerator.o 2> ../../logs/win/rng.log
	$(GCC) ../../src/BitmapUtil.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BitmapUtil.o 2> ../../logs/win/bitmaputil.log
	$(GCC) ../../src/sdl_surface_load_image_wrapper.cpp $(LIBS) $(FLAGS) -c -o ../../obj/sdl_surface_load_image_wrapper.o 2> ../../logs/win/imagesurface.log
	$(GCC) ../../src/Texture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Texture.o 2> ../../logs/win/texture.log
	$(GCC) ../../src/ParticleGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleGenerator.o 2> ../../logs/win/particlegen.log
	$(GCC) ../../src/ParticleRenderer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleRenderer.o 2> ../../logs/win/particlerender.log
	$(GCC) ../../src/ClockTimer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ClockTimer.o 2> ../../logs/win/clocktimer.log
	$(GCC) ../../src/Player.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Player.o 2> ../../logs/win/player.log
	$(GCC) ../../src/Block.cpp $(LIBS) $(FLAGS) -c -o ../../obj/block.o 2> ../../logs/win/block.log
	$(GCC) ../../src/Entity.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Entity.o 2> ../../logs/win/entity.log
	$(GCC) ../../src/BasicEnemy.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BasicEnemy.o 2> ../../logs/win/basicenemy.log
	$(GCC) ../../src/JumpingEnemy.cpp $(LIBS) $(FLAGS) -c -o ../../obj/JumpingEnemy.o 2> ../../logs/win/jumpingenemy.log
	$(GCC) ../../src/Game.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Game.o 2> ../../logs/win/game.log
link:
	$(GCC) $(OBJ_FILES) $(LIBS) $(FLAGS) -o ../../bin/Game.exe 2> ../../logs/linker_windows.log
clean:
	rm ../../obj/*.o
exec:
	../../bin/Game.exe > ../../logs/output_stdout.log
