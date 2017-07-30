#include "Game.h"
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include "Block.h"
#include "Player.h"

const int w = 1366;
const int h = 768;

std::vector<Block> blocks;
// I'm likely going to stre a different vector for different enemy types.
std::vector<BasicEnemy> basicEnemies;
std::vector<JumpingEnemy> jumpingEnemies;
Player p(Vec2(300, 300), Vec2(73, 73), Vec2(100), Vec4(1.0, 0.0, 0.0, 1.0));
Game::Game(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	win = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
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
	pp = std::make_shared<PostProcessor>(ctx, w, h);
	player_texture = std::make_shared<ImageTexture>( ctx, "textures//test_player.png" );
	wall_texture = std::make_shared<ImageTexture>( ctx, "textures//wall_test.png" );
	ls->setProj(proj);
	// basic scene.
	blocks.push_back(Block(Vec2(0, 620), Vec2(2280, 100), Vec4(0.4, 0.0, 0.0, 1.0), BlockTypes::Ceiling));
	blocks.push_back(Block(Vec2(0, 0), Vec2(1280, 100), Vec4(0.4, 0.0, 0.0, 1.0)));
	blocks.push_back(Block(Vec2(0, 0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	blocks.push_back(Block(Vec2(500, 500), Vec2(80, 160), Vec4(.2), BlockTypes::Wall));
	blocks.push_back(Block(Vec2(2260, 0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	blocks.push_back(Block(Vec2(300, 520), Vec2(100)));
	blocks.push_back(Block(Vec2(900, 220), Vec2(100, 320)));
	blocks.push_back(Block(Vec2(600, 320), Vec2(100, 30)));
	blocks.push_back(Block(Vec2(400, 400), Vec2(100, 10)));
	basicEnemies.push_back(BasicEnemy(Vec2(480, 300), Vec2(20, 50), Vec2(100), Vec4(1)));
	basicEnemies.push_back(BasicEnemy(Vec2(700, 100), Vec2(50, 50), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
	jumpingEnemies.push_back(JumpingEnemy(Vec2(500, 300), Vec2(20, 40), Vec2(150), Vec4(1, 0, 0, 1)));
	basicEnemies.push_back(BasicEnemy(Vec2(840, 100), Vec2(50, 120), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
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

float camX=0;
float camY=0;
void Game::draw(){
	ctx->clearColor(0.0, 0.0, 0.1f, 0.0);
	ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
	ctx->viewport(0, 0, w, h);
	ctx->enableAlpha();
	pp->begin();
		view = glm::mat4();
		ls->use();
		ls->setTex(0);
		ls->setTextured(false);
		for(int i = 0; i < 10; ++i){
			ls->setLight(i, lights[i]);
		}
		sb->draw(Vec2(0),Vec4(0),Vec2(5000, 5000), Vec4(0.1, 0.1, 0.1, 1.0));
		sb->render();
		ls->setTextured(true);
		wall_texture->bind();
		for(auto &b: blocks){
			sb->draw(b.getPos(), b.getUvs(), b.getSize(), b.getColor());
		}
		sb->render();

		ls->setTextured(false);
		for(auto &be : basicEnemies)
		sb->draw(be.getPos(), Vec4(0), be.getSize(), be.getColor());
		for(auto &be : jumpingEnemies)
		sb->draw(be.getPos(), Vec4(0), be.getSize(), be.getColor());
		sb->render();

		ls->setTextured(true);
		player_texture->bind();
		sb->draw(p.getPos(), p.getUvs(), p.getSize(), Vec4(p.getColor().r(), p.getColor().g(), p.getColor().b(), 1.0));
		sb->render();
		ls->unuse();

		camX = -p.getPos().x() + w/2.0f;
		camY = -p.getPos().y() + h/2.0f;

		if(camX < -2280+w){
			camX = -2280+w;
		}

		view = glm::translate(view, glm::vec3(camX,camY,0));
	pp->end();
	ls->setView(view);

	SDL_GL_SwapWindow(win);
}
