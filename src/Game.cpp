#include "Game.h"



struct player{
	player( const player& other ) = default;
	player() : pos (250, 520-205), size(23, 75), velocity(100, 100){ }
	Vec2 pos;
	Vec2 size;
	Vec2 velocity;
	float jmpDelay = 10;
	bool ground=false;
	bool jetpack=false;
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
bool aabb( block& b, player& p ){
	return (p.pos.x() < b.pos.x() + b.size.x() && p.pos.x() + p.size.x() > b.pos.x())&&
	       (p.pos.y() < b.pos.y() + b.size.y() && p.pos.y() + p.size.y() > b.pos.y());
}

void Game::update(){
	ClockTimer::Tick();
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			active = false;
		}
	}
	const Uint8* keys=SDL_GetKeyboardState(NULL);
	// reset velocity every frame so we don't move in one direction forever.
	p.velocity.x() = 0;
	if(keys[SDL_SCANCODE_A]){
		p.velocity.x() = -150;
	}
	if(keys[SDL_SCANCODE_D]){
		p.velocity.x() = 150;
	}
	if(keys[SDL_SCANCODE_W]){
		p.jetpack = !p.jetpack;
	}
	if(keys[SDL_SCANCODE_SPACE]){
		/*
		 * enhances the platformy feel by having variable jumps :)
		 */
		if(p.ground == false && p.jmpDelay > 0){
			p.velocity.y() -= 105 * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
			p.jmpDelay -= ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
		}
		if(p.ground == true && !p.jetpack){
			p.velocity.y() = -205.0f ;
			p.ground = false;
		}
		else if (p.jetpack){
			p.velocity.y() -= 300.0f * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
		}
	}
	
	// re apply gravity
	p.velocity.y() += 266.0f * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);

	player pred = p; // make clone.
	pred.pos.x() += p.velocity.x() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
	for(auto &b : blocks){
		// simulate movement
		if(aabb( b, pred )){
			p.velocity.x() = 0;
			//p.pos.x() += -(p.velocity.x()) * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
			break;
		}
	}
	pred = p; // make clone.
	pred.pos.y() += p.velocity.y() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);

	for(auto &b : blocks){
		// simulate movement
		// by predicating what will happen in the next frame.
		if(aabb( b, pred )){
			// if my prediction frame touchs something we cannot move.
			p.velocity.y() = 0;
			// check if I hit the bottom
			// of the block since pos.y + size.y = bottom in a traditional orthographic matrix.
			if( b.pos.y() + b.size.y() < p.pos.y() ){
			}else{
			p.ground = true;
			}
			break;
		}
	}
	if(p.ground == true){
		p.jmpDelay = 10;
	}
	/*
	 * I calculate gravity at the very end :)
	 */
	p.pos.y() += p.velocity.y()*ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
	p.pos.x() += p.velocity.x() * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
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
		sb->draw(p.pos, Vec4(0), p.size, Vec4(1.0, 0.0, 0.0, 1.0));
		sb->render();
		ls->unuse();
	pp->end();

	SDL_GL_SwapWindow(win);
}
