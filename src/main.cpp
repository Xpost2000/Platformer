#include <iostream>
#include <time.h>
#include "ClockTimer.h"

#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"
#include "DefaultShader.h"
#include "SpriteBatcher.h"
#include "RandomNumberGenerator.h"
#include "ParticleGenerator.h"
#include "LightShader.h"
#include "Postprocessor.h"
#include <vector>
#define WIDTH 1280
#define HEIGHT 720

struct Sprite{
	Sprite(float x, float y, float w, float h, float uX, float uY, float uW, float uH, float brns) : x(x), y(y), w(w), h(h), uX(uX), uY(uY), uW(uW), uH(uH), brns(brns) {}
	float x, y;
	float w, h;
	float uX, uY;
	float uW, uH;
	float brns;
};
std::vector<Sprite> sprites;
#define MAX_TM_SZ 28
#define TL_SZ 90
int tilemap[MAX_TM_SZ][MAX_TM_SZ] = {
	{3, 3, 3, 3, 3},
	{3, 5, 5, 5, 3, 3, 3},
	{3, 5, 5, 5, 5, 5, 5},
	{1, 1, 1, 1, 1, 3, 3,},
	{2, 2, 2, 2, 2, 3,3},
	{2, 2, 2, 2, 2, 3,3,3,1,1,1,1,1,1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,2 ,2 },
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
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
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Test Letter X Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
	int index = 0;

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	ptrs::ImageTexture tex = std::make_shared<ImageTexture>(ctx,"grass.png");
	SpriteBatcher sb(ctx);
	DefaultShader ds(ctx);
	LightShader ls(ctx);
	PostProcessor pp (ctx, WIDTH, HEIGHT);
	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4();
	view = glm::scale(view, glm::vec3(0.6, 0.6, 1.0));
	ds.setMatrices(proj, view);
	ls.setView(view);
	ls.setProj(proj);
	process_tm();
	ParticleGenerator pg(Vec2(1280/2, 720/2), Vec2(800, -400), Vec2(80, -10), Vec2(40), Vec4(0.1, 0.1, 0.1, 0.5), 100, Vec2(-10, 40), Vec2(-30, 30), Vec2(-30, 50), 1200);
	ParticleGenerator pa(Vec2(1280/2+400, 720/2), Vec2(800, 160), Vec2(80, 20), Vec2(20), Vec4(0.1, 0.4, 1.0, 0.5), 110, Vec2(-10, 40), Vec2(-10, 10), Vec2(-30, 50), 1700);
	Light l[10];
	l[0] = Light(600,  Vec3(1, 0, 0), Vec2(300, 500));
	l[1] = Light(200,  Vec3(0, 0, 1), Vec2(600, 500));
	while(true){
		ClockTimer::Tick();
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
			if(ev.type == SDL_KEYDOWN){
			}
			else{
			}
		}
		ctx->clearColor(0.0, 0.0, 0.0);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->enableAlpha();
		ctx->viewport(0, 0, WIDTH, HEIGHT);
		pp.begin();
		ls.use();	
		ls.setTextured(true);
		tex->bind();
		for(int i = 0; i < 10; ++i){
			ls.setLight(i, l[i]);
		}
		for( auto& sp : sprites ){
			sb.draw(Vec2(sp.x, sp.y), Vec4(sp.uX, sp.uY, sp.uW, sp.uH), Vec2(sp.w, sp.h), Vec4(sp.brns, sp.brns, sp.brns, 1.0f));
		}
		sb.render();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for(auto& p : pg.get_particles()){
			sb.draw(p.pos, Vec4(0), p.size, p.color);
		}
		sb.render();
		for(auto& p : pa.get_particles()){
			sb.draw(p.pos, Vec4(0), p.size, p.color);
		}
		sb.render();
		pg.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		pa.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		ds.unuse();
		pp.end();

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
