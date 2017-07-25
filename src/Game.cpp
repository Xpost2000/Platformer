#include "Game.h"



struct player{
	player() : pos (0, 520-95), size(23, 75), velocity(100, 100){ }
	Vec2 pos;
	Vec2 size;
	Vec2 velocity;
}p;
struct block{
	block(Vec2 pos, Vec2 size) : pos(pos), size(size){}
	Vec2 pos;
	Vec2 size;
};

std::vector<block> blocks;
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
	blocks.push_back(block(Vec2(300, 520), Vec2(100)));
	blocks.push_back(block(Vec2(600, 320), Vec2(100, 30)));
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
bool aabb( block& b, player& p ){
	return (p.pos.x() < b.pos.x() + b.size.x() && p.pos.x() + p.size.x() > b.pos.x())&&
	       (p.pos.y() < b.pos.y() + b.size.y() && p.pos.y() + p.size.y() > b.pos.y());
}
void blockCollide( block& b, player& p, float dt ){
		float pBottom = p.pos.y() + p.size.y();
		float oBottom = b.pos.y() + b.size.y();
		float pRight = p.pos.x() + p.size.x();
		float oRight = b.pos.x() + b.size.x();

		// our bottom to their top
		float tCollide = pBottom - b.pos.y();
		// their bottom to our top
		float bCollide = oBottom - p.pos.y();
		float rCollide = oRight - p.pos.x();
		float lCollide = pRight - b.pos.x();

		if (tCollide < bCollide && tCollide < lCollide && tCollide < rCollide){
			p.pos.y() -= p.velocity.y()*dt;
		}
		if (bCollide < tCollide && bCollide < lCollide && bCollide < rCollide){
			p.pos.y() += p.velocity.y()*dt;
		}
		if (lCollide < rCollide && lCollide < tCollide && lCollide < bCollide){
			p.pos.x() -= abs(p.velocity.x())*dt;
		}
		if (rCollide < lCollide && rCollide < tCollide && rCollide < bCollide){
			p.pos.x() += abs(p.velocity.x())*dt;
		}
}
void Game::update(){
	ClockTimer::Tick();
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			active = false;
		}
	}
	const Uint8* keys=SDL_GetKeyboardState(NULL);
	if(p.pos.y() >= 620-75){
		p.velocity.y() = 0;
		p.velocity.x() = 150;
	}
	else{
		p.velocity.y() += 320*ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
	}
	if(keys[SDL_SCANCODE_A]){
		if(p.pos.x() > 0){
		p.pos.x() -= p.velocity.x() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
		}
	}
	if(keys[SDL_SCANCODE_D]){
		if(p.pos.x()+p.size.x() < 1280){
		p.pos.x() += p.velocity.x() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
		}
	}
	if(keys[SDL_SCANCODE_SPACE]){
		p.velocity.y() += -780*ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
	}
	for(auto &b: blocks){
		if(aabb(b, p))
		blockCollide(b, p, ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
	}

	p.pos.y() += p.velocity.y() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
}

Light lights[10] ={
	Light(5000, Vec3(1), Vec2(500)),
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
		sb->draw(Vec2(0, 620), Vec4(0), Vec2(1280, 100), Vec4(0.3));
		for(auto &b: blocks){
			sb->draw(b.pos, Vec4(0), b.size, Vec4(0.3));
		}
		sb->draw(p.pos, Vec4(0), p.size, Vec4(1.0, 0.0, 0.0, 1.0));
		sb->render();
		ls->unuse();
	pp->end();

	SDL_GL_SwapWindow(win);
}
