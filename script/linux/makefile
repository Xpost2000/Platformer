GCC=g++
LIBS=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lGLEW -lGL -lfreetype
FLAGS=-std=gnu++14 -Wall -O3 -DGAME_BUILD=110 -I/usr/include/freetype2
OBJ_FILES= ../../obj/IDevice.o\
	  ../../obj/IObjectHandle.o\
	  ../../obj/LightShader.o\
	  ../../obj/Buffer.o\
	  ../../obj/Level.o\
	  ../../obj/LevelList.o\
	  ../../obj/Config.o\
	  ../../obj/ParticleGenerator.o\
	  ../../obj/ParticleRenderer.o\
	  ../../obj/VertexArray.o\
	  ../../obj/BufferTypes.o\
	  ../../obj/BitmapTextRenderer.o\
	  ../../obj/FreeTypeText.o\
	  ../../obj/GLDevice.o\
	  ../../obj/ClockTimer.o\
	  ../../obj/Shader.o\
	  ../../obj/GameCamera.o\
	  ../../obj/Player.o\
	  ../../obj/TextureManager.o\
	  ../../obj/BasicEnemy.o\
	  ../../obj/JumpingEnemy.o\
	  ../../obj/IShaderSet.o\
	  ../../obj/ImageTexture.o\
	  ../../obj/DefaultShader.o\
	  ../../obj/TestShader.o\
	  ../../obj/TextShader.o\
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
	  ../../obj/Window.o\
	  ../../obj/EntityManager.o\
	 ../../obj/Game.o\
	 ../../obj/main.o\
	 ../../obj/Sound.o
all:
	$(GCC) ../../src/main.cpp $(LIBS) $(FLAGS) -c -o ../../obj/main.o 2> ../../logs/linux/main.log
	$(GCC) ../../src/IObjectHandle.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IObjectHandle.o 2> ../../logs/linux/objHandle.log
	$(GCC) ../../src/LightShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/LightShader.o 2> ../../logs/linux/lightShader.log
	$(GCC) ../../src/Buffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Buffer.o 2> ../../logs/linux/buffer.log
	$(GCC) ../../src/VertexArray.cpp $(LIBS) $(FLAGS) -c -o ../../obj/VertexArray.o 2> ../../logs/linux/vertexarray.log
	$(GCC) ../../src/IDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IDevice.o 2> ../../logs/linux/idevice.log
	$(GCC) ../../src/BufferTypes.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BufferTypes.o 2> ../../logs/linux/buffertypes.log
	$(GCC) ../../src/GLDevice.cpp $(LIBS) $(FLAGS) -c -o ../../obj/GLDevice.o 2> ../../logs/linux/gldevice.log
	$(GCC) ../../src/Shader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Shader.o 2> ../../logs/linux/shader.log
	$(GCC) ../../src/IShaderSet.cpp $(LIBS) $(FLAGS) -c -o ../../obj/IShaderSet.o 2> ../../logs/linux/ishaderset.log
	$(GCC) ../../src/DefaultShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/DefaultShader.o 2> ../../logs/linux/defaultshader.log
	$(GCC) ../../src/TestShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TestShader.o 2> ../../logs/linux/testshader.log
	$(GCC) ../../src/TextShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TextShader.o 2> ../../logs/linux/textshader.log
	$(GCC) ../../src/PostProcessorShader.cpp $(LIBS) $(FLAGS) -c -o ../../obj/PostProcessorShader.o 2> ../../logs/linux/postprocessorshader.log
	$(GCC) ../../src/ShaderProgram.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderProgram.o 2> ../../logs/linux/shaderprogram.log
	$(GCC) ../../src/vectors.cpp $(LIBS) $(FLAGS) -c -o ../../obj/vectors.o 2> ../../logs/linux/vectors.log
	$(GCC) ../../src/ShaderUniform.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ShaderUniform.o 2> ../../logs/linux/shaderuniform.log
	$(GCC) ../../src/SpriteBatcher.cpp $(LIBS) $(FLAGS) -c -o ../../obj/SpriteBatcher.o 2> ../../logs/linux/spritebatcher.log
	$(GCC) ../../src/Bitmap.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Bitmap.o 2> ../../logs/linux/bitmap.log
	$(GCC) ../../src/FreeTypeText.cpp $(LIBS) $(FLAGS) -c -o ../../obj/FreeTypeText.o 2> ../../logs/linux/text.log
	$(GCC) ../../src/Renderbuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Renderbuffer.o 2> ../../logs/linux/renderbuffer.log
	$(GCC) ../../src/Framebuffer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Framebuffer.o 2> ../../logs/linux/framebuffer.log
	$(GCC) ../../src/Postprocessor.cpp $(LIBS) $(FLAGS) -c -o ../../obj/PostProcessor.o 2> ../../logs/linux/postprocessor.log
	$(GCC) ../../src/ImageTexture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ImageTexture.o 2> ../../logs/linux/imagetexture.log
	$(GCC) ../../src/RandomNumberGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/RandomNumberGenerator.o 2> ../../logs/linux/rng.log
	$(GCC) ../../src/BitmapUtil.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BitmapUtil.o 2> ../../logs/linux/bitmaputil.log
	$(GCC) ../../src/sdl_surface_load_image_wrapper.cpp $(LIBS) $(FLAGS) -c -o ../../obj/sdl_surface_load_image_wrapper.o 2> ../../logs/linux/imagesurface.log
	$(GCC) ../../src/Texture.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Texture.o 2> ../../logs/linux/texture.log
	$(GCC) ../../src/ParticleGenerator.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleGenerator.o 2> ../../logs/linux/particlegen.log
	$(GCC) ../../src/ParticleRenderer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ParticleRenderer.o 2> ../../logs/linux/particlerender.log
	$(GCC) ../../src/ClockTimer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/ClockTimer.o 2> ../../logs/linux/clocktimer.log
	$(GCC) ../../src/Player.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Player.o 2> ../../logs/linux/player.log
	$(GCC) ../../src/Block.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Block.o 2> ../../logs/linux/block.log
	$(GCC) ../../src/Entity.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Entity.o 2> ../../logs/linux/entity.log
	$(GCC) ../../src/BasicEnemy.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BasicEnemy.o 2> ../../logs/linux/basicenemy.log
	$(GCC) ../../src/BitmapTextRenderer.cpp $(LIBS) $(FLAGS) -c -o ../../obj/BitmapTextRenderer.o 2> ../../logs/linux/bmtxtrnder.log
	$(GCC) ../../src/JumpingEnemy.cpp $(LIBS) $(FLAGS) -c -o ../../obj/JumpingEnemy.o 2> ../../logs/linux/jumpingenemy.log
	$(GCC) ../../src/Game.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Game.o 2> ../../logs/linux/game.log
	$(GCC) ../../src/Config.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Config.o 2> ../../logs/linux/config.log
	$(GCC) ../../src/Window.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Window.o 2> ../../logs/linux/window.log
	$(GCC) ../../src/TextureManager.cpp $(LIBS) $(FLAGS) -c -o ../../obj/TextureManager.o 2> ../../logs/linux/texturemanager.log
	$(GCC) ../../src/LevelList.cpp $(LIBS) $(FLAGS) -c -o ../../obj/LevelList.o 2> ../../logs/linux/levellist.log
	$(GCC) ../../src/Level.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Level.o 2> ../../logs/linux/Level.log
	$(GCC) ../../src/GameCamera.cpp $(LIBS) $(FLAGS) -c -o ../../obj/GameCamera.o 2> ../../logs/linux/GameCamera.log
	$(GCC) ../../src/EntityManager.cpp $(LIBS) $(FLAGS) -c -o ../../obj/EntityManager.o 2> ../../logs/linux/EntityManager.log
	$(GCC) ../../src/Sound.cpp $(LIBS) $(FLAGS) -c -o ../../obj/Sound.o 2> ../../logs/linux/Sound.log
link:
	$(GCC) $(OBJ_FILES) $(LIBS) $(FLAGS) -o ../../bin/Game_linux 2> ../../logs/linker_linux.log
clean:
	rm ../../obj/*.o
exec:
	../../bin/Game_linux
