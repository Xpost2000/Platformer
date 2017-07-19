#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"
#include "DefaultShader.h"
#include "SpriteBatcher.h"
#include "Postprocessor.h"
#define WIDTH 1280
#define HEIGHT 720
float x = 200;
float y = 0;
int main(int argc, char** argv){
	SDL_Window* window;
	SDL_Event ev;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Test Letter X OGL Wrapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	gl_info_struct_t info = {
		3,
		3,
		24,
		16,
		24,
		24,
		24,
		24,
		true,
		true,
		CORE_CONTEXT
	};
	ptrs::IDevice ctx = std::make_shared<GLDevice>(window, info);
	std::map<std::string, ptrs::Texture> m;
	ptrs::Texture tex;
	int index = 0;

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	tex = ctx->createTexture(ctx);
	// using delegated constructor
	ImageSurface es("grass.png");
	Bitmap bm (es.surf, PixelFormat::RGBA);
	ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_T , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_S , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	tex->texImage2D(TextureTarget::TEXTURE2D, bm, 0, 0, GL_UNSIGNED_BYTE);	
	ctx->genMipmaps( TextureTarget::TEXTURE2D );
	
	ctx->unbindTexture( TextureTarget::TEXTURE2D );

	SpriteBatcher sb(ctx);
	DefaultShader ds(ctx);
	PostProcessor pp (ctx, WIDTH, HEIGHT);
	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4();
	ds.setMatrices(proj, view);
	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
			if(ev.type == SDL_KEYDOWN){
				x += 10;
			}
			else{
			}
		}
		ctx->clearColor(0.0, 0.0, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, WIDTH, HEIGHT);
		pp.begin();
		ds.use();
	
		ds.setTextured(true);
		ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
		sb.draw(Vec2(x, 500), Vec4(0.0f, 0.0f, 512.0f/2048.0f, 512.0f/2048.0f), Vec2(300, 300), Vec3(1));
		sb.render();

		ds.unuse();
		pp.end();

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
