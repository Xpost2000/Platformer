#include <iostream>
#include <time.h>

#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"
#include "DefaultShader.h"
#include "SpriteBatcher.h"
#include "Postprocessor.h"
#include <vector>
#define WIDTH 1280
#define HEIGHT 720

float y = 300.0;
float delay = 0.0f;
struct Sprite{
	Sprite(float x, float y, float w, float h, float uX, float uY, float uW, float uH, float brns) : x(x), y(y), w(w), h(h), uX(uX), uY(uY), uW(uW), uH(uH), brns(brns) {}
	float x, y;
	float w, h;
	float uX, uY;
	float uW, uH;
	float brns;
};
struct Particle{
	Particle(float x, float y, float w, float h, float r, float g, float b) : x(x), y(y), w(w), h(h), r(r), g(g), b(b){}
	void update(){ 
		x+=32.0f+spread; 
		y+=2.5f+spread;
		lifeTime--;
	}
	float lifeTime = 100;
	float x, y;
	float spread;
	float w, h;
	float r, g, b;
};
std::vector<Sprite> sprites;
std::vector<Particle> particles;
#define MAX_TM_SZ 18
#define TL_SZ 90
int tilemap[MAX_TM_SZ][MAX_TM_SZ] = {
	{3, 3, 3, 3, 3},
	{3, 5, 5, 5, 3},
	{3, 5, 5, 5, 5},
	{1, 1, 1, 1, 1, 3,},
	{2, 2, 2, 2, 2, 3,3},
	{2, 2, 2, 2, 2, 3,3,1,1,1,1,1,1,1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

void process_tm(){
	for(int y = 0; y < MAX_TM_SZ; y++){
		for(int x = 0; x < MAX_TM_SZ; x++){
			switch(tilemap[y][x]){
				case 3:
					sprites.push_back(Sprite(x*TL_SZ, y*TL_SZ, TL_SZ, TL_SZ, 0, 514.0f/2048.0f, 420.0f/2048.0f, 934.0f/2048.0f, 1));	
					break;
				case 2:
					sprites.push_back(Sprite(x*TL_SZ, y*TL_SZ, TL_SZ, TL_SZ, 0, 0, 512.0f/2048.0f, 512.0f/2048.0f, 1));	
					break;
				case 1:
					sprites.push_back(Sprite(x*TL_SZ, y*TL_SZ, TL_SZ, TL_SZ, 514.0f/2048.0f, 0, 1026.0f/2048.0f, 512.0f/2048.0f, 1));	
					break;
				case 5:
					sprites.push_back(Sprite(x*TL_SZ, y*TL_SZ, TL_SZ, TL_SZ, 0, 514.0f/2048.0f, 420.0f/2048.0f, 934.0f/2048.0f, 0.5));	
					break;
				default:
					break;
			};
		}
	}
}

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
	process_tm();
	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
			if(ev.type == SDL_KEYDOWN){
			}
			else{
			}
		}
		srand(time(0));
		ctx->clearColor(0.0, 0.0, 0.2);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, WIDTH, HEIGHT);
		pp.begin();
		ds.use();	
		if(delay <= 0 ){
			particles.push_back(Particle(240, y-5, 15, 15, 0.8, 0.0, 0.0));
			particles.push_back(Particle(220, y-20, 19, 19, 0.8, 0.0, 0.0));
			particles.push_back(Particle(200, y+15, 19, 19, 0.8, 0.0, 0.0));
			particles.push_back(Particle(200, y-15, 10, 10, 0.8, 0.0, 0.0));
			particles.push_back(Particle(200, y+10, 20, 20, 0.8, 0.0, 0.0));
			particles.push_back(Particle(200, y-10, 20, 20, 0.8, 0.0, 0.0));
			delay = 50;
			std::cout << delay << std::endl;	
		}
		else{
			delay--;
		}
		particles.back().spread = rand() % 15+1;
		ds.setTextured(true);
		ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
		for( auto& sp : sprites ){
			sb.draw(Vec2(sp.x, sp.y), Vec4(sp.uX, sp.uY, sp.uW, sp.uH), Vec2(sp.w, sp.h), Vec3(sp.brns));
		}
		sb.render();
		ds.setTextured(false);
		for( auto& p : particles ){
			if(p.lifeTime < 0){
				// would mark as dead.	
			}
			p.update();
			sb.draw(Vec2(p.x, p.y), Vec4(0, 0, 0, 0), Vec2(p.w, p.h), Vec3(p.r, p.g, p.b));
		}
		sb.render();
		ds.unuse();
		pp.end();

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
