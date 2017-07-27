#include "Game.h"
#include "Player.h"

std::vector<block> blocks;
Player p(Vec2(300, 300), Vec2(20, 50), Vec2(100), Vec4(0));
Game::Game(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	win = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	gl_info_struct_t info ={
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
	ctx = std::make_shared<GLDevice>(win, info);
	pr = std::make_shared<ParticleRenderer>(ctx);
	sb = std::make_shared<SpriteBatcher>(ctx);
	ls = std::make_shared<LightShader>(ctx);
	pp = std::make_shared<PostProcessor>(ctx, 1280, 720);
	ls->setView(view);
	ls->setProj(proj);
	blocks.push_back(block(Vec2(0, 620), Vec2(1280, 100)));
	blocks.push_back(block(Vec2(0, 0), Vec2(1280, 100)));
	blocks.push_back(block(Vec2(300, 520), Vec2(100)));
	blocks.push_back(block(Vec2(600, 320), Vec2(100, 30)));
	blocks.push_back(block(Vec2(400, 400), Vec2(100, 10)));
}
Game::~Game(){
	SDL_DestroyWindow(win);
}
void Game::run(){
	while(active){
		update();
		draw();
	}
}
void Game::update(){
	ClockTimer::Tick();
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			active = false;
		}
	}
	p.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), blocks);
}

Light lights[10] ={
	Light(3000, Vec3(1), Vec2(500)),
	Light(),
	Light(),
	Light(),
	Light(),
	Light(),
	Light(),
	Light(),
	Light(),
	Light()
};

void Game::draw(){
	ctx->clearColor(0.0, 0.0, 0.1f);
	ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
	ctx->viewport(0, 0, 1280, 720);
	pp->begin();
		ls->use();
		for(int i = 0; i < 10; ++i){
			ls->setLight(i, lights[i]);
		}
		sb->draw(Vec2(0),Vec4(0),Vec2(1280, 720), Vec4(0.0, 0.0, 0.1, 1.0));
		for(auto &b: blocks){
			sb->draw(b.pos, Vec4(0), b.size, Vec4(0.3));
		}
		sb->draw(p.pos, Vec4(0), p.size, Vec4(p.color.r(), p.color.g(), p.color.b(), 1.0));
		sb->render();
		ls->unuse();
	pp->end();

	SDL_GL_SwapWindow(win);
}
