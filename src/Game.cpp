#include "Game.h"
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include "Block.h"
#include "Player.h"

std::vector<Block> blocks;
// I'm likely going to stre a different vector for different enemy types.
std::vector<BasicEnemy> basicEnemies;
std::vector<JumpingEnemy> jumpingEnemies;
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
	// basic scene.
	blocks.push_back(Block(Vec2(0, 620), Vec2(1280, 100), Vec4(0.4, 0.0, 0.0, 1.0)));
	blocks.push_back(Block(Vec2(0, 0), Vec2(1280, 100), Vec4(0.4, 0.0, 0.0, 1.0)));
	blocks.push_back(Block(Vec2(0, 0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	blocks.push_back(Block(Vec2(1260, 0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	blocks.push_back(Block(Vec2(300, 520), Vec2(100)));
	blocks.push_back(Block(Vec2(900, 220), Vec2(100, 320)));
	blocks.push_back(Block(Vec2(600, 320), Vec2(100, 30)));
	blocks.push_back(Block(Vec2(400, 400), Vec2(100, 10)));
//	basicEnemies.push_back(BasicEnemy(Vec2(480, 300), Vec2(20, 50), Vec2(100), Vec4(1)));
//	basicEnemies.push_back(BasicEnemy(Vec2(700, 100), Vec2(50, 50), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
	jumpingEnemies.push_back(JumpingEnemy(Vec2(500, 300), Vec2(20, 100), Vec2(150), Vec4(1, 0, 0, 1)));
//	basicEnemies.push_back(BasicEnemy(Vec2(840, 100), Vec2(50, 120), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
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
bool Simactive;
void Game::update(){
	ClockTimer::Tick();
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			active = false;
		}
		if(ev.key.keysym.sym == SDLK_z){
			Simactive = false;
		}
		if(ev.key.keysym.sym == SDLK_x){
			Simactive = true;
		}
	}
	if(Simactive){
	for(int i = 0; i < basicEnemies.size(); ++i){
		if(basicEnemies[i].isDead()){
			if(basicEnemies[i].DeathAnimation(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS)))
			basicEnemies.erase(basicEnemies.begin() + i);
		}
		basicEnemies[i].update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), blocks);
	}
	for(int i = 0; i < jumpingEnemies.size(); ++i){
		if(jumpingEnemies[i].isDead()){
			if(jumpingEnemies[i].DeathAnimation(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS)))
			jumpingEnemies.erase(jumpingEnemies.begin() + i);
		}
		jumpingEnemies[i].update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), blocks);
	}
	p.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), blocks, basicEnemies, jumpingEnemies);
	}
}

Light lights[10] ={
	Light(2000, Vec3(1), Vec2(500)),
	Light(5000, Vec3(0.9, 0.5, 0.2), Vec2(800, 500)),
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
	ctx->clearColor(0.0, 0.0, 0.1f, 0.0);
	ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
	ctx->viewport(0, 0, 1280, 720);
	ctx->enableAlpha();
	pp->begin();
		ls->use();
		for(int i = 0; i < 10; ++i){
			ls->setLight(i, lights[i]);
		}
		sb->draw(Vec2(0),Vec4(0),Vec2(5000, 5000), Vec4(0.1, 0.1, 0.1, 1.0));
		for(auto &b: blocks){
			sb->draw(b.getPos(), Vec4(0), b.getSize(), b.getColor());
		}
		for(auto &be : basicEnemies)
		sb->draw(be.getPos(), Vec4(0), be.getSize(), be.getColor());
		for(auto &be : jumpingEnemies)
		sb->draw(be.getPos(), Vec4(0), be.getSize(), be.getColor());

		sb->draw(p.getPos(), Vec4(0), p.getSize(), Vec4(p.getColor().r(), p.getColor().g(), p.getColor().b(), 1.0));
		sb->render();
		ls->unuse();
	pp->end();

	SDL_GL_SwapWindow(win);
}
