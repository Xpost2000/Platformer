#include "Game.h"
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include "Block.h"
#include "Player.h"

// I'm likely going to stre a different vector for different enemy types.
Player p(Vec2(300, 300), Vec2(73, 73), Vec2(100), Vec4(1.0, 1.0, 1.0, 1.0));
Game::Game(){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	cfg.read_config();
	w = cfg.get_window_width();
	h = cfg.get_window_height();
	start = uiButton(Vec2(0+100, h/2.0f + 50), Vec2(300, 60), Vec3(1.0), Vec3(1.0, 0.0, 0.0), ButtonType::Start);
	option = uiButton(Vec2(0+100, h/2.0f + 120), Vec2(300, 60), Vec3(1.0), Vec3(0.0, 1.0, 0.0), ButtonType::Options);
	quit = uiButton(Vec2(0+100, h/2.0f + 180), Vec2(300, 60), Vec3(1.0), Vec3(0.0, 0.0, 1.0), ButtonType::Quit);
	game_name = cfg.get_game_name();
	std::cout << "Level List Directory ::" << cfg.get_lvl_list_dir() + cfg.get_lvl_list_file() << std::endl;
	std::cout << "Texture Files Directory ::" << cfg.get_texture_dir() << std::endl;
	std::cout << "Level Files Directory ::" << cfg.get_level_dir() << std::endl;
	std::cout << "Sound Files Directory ::" << cfg.get_sounds_dir() << std::endl;
	std::cout << "\n\nEntries in the level list\n";
	lst.read(cfg.get_lvl_list_dir() + cfg.get_lvl_list_file());
	for( auto &ent : lst.entries ){
		std::cout << ent << std::endl;
	}
	proj = glm::ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
	window = std::make_shared<Window>(w, h, game_name);
	window->spawn();
	window->set_vsync(cfg.get_vsync_flag());
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
	ctx = std::make_shared<GLDevice>(window->get_handle(), info);
	pr = std::make_shared<ParticleRenderer>(ctx);
	sb = std::make_shared<SpriteBatcher>(ctx);
	ls = std::make_shared<LightShader>(ctx);
	pp = std::make_shared<PostProcessor>(ctx, w, h);
	tm.add_texture("wall", "textures//wall_test.png", ctx);
	tm.add_texture("player", "textures//test_player.png", ctx);
	tm.add_texture("ui-menu", "textures//ui//ui_atlas.png", ctx);
	ls->setProj(proj);
	em.create_block(Block(Vec2(0, 620), Vec2(2280, 100), Vec4(0.4, 0.0, 0.0, 1.0)));
	em.create_block(Block(Vec2(0, 0), Vec2(1280,100), Vec4(0.4, 0.0, 0.0, 1.0)));
	em.create_block(Block(Vec2(0,0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	em.create_block(Block(Vec2(500), Vec2(80, 160), Vec4(.2), BlockTypes::Wall));
	em.create_block(Block(Vec2(2260, 0), Vec2(20, 720), Vec4(0.0, 0.0, 0.2, 1.0)));
	em.create_block(Block(Vec2(300, 520), Vec2(100)));
	em.create_block(Block(Vec2(900, 220), Vec2(100, 320)));
	em.create_block(Block(Vec2(600, 320), Vec2(100, 30)));
	em.create_block(Block(Vec2(400, 400), Vec2(100, 10)));
	em.create_enemy(BasicEnemy(Vec2(880, 300), Vec2(20, 50), Vec2(100), Vec4(1)));
	em.create_enemy(BasicEnemy(Vec2(700, 100), Vec2(50, 50), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
	em.create_enemy(JumpingEnemy(Vec2(500, 300), Vec2(20, 40), Vec2(150), Vec4(1, 0, 0, 1)));
	em.create_enemy(BasicEnemy(Vec2(2000, 100), Vec2(50, 120), Vec2(160), Vec4(0.0, 1.0, 0.0, 1.0)));
}
Game::~Game(){
	SDL_Quit();
}
void Game::run(){
	while(!window->should_close()){
		update();
		draw();
	}
}
int mX;
int mY;
void Game::update(){
	ClockTimer::Tick();
	SDL_GetMouseState(&mX, &mY);
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			window->set_should_close(true);
		}
		if(ev.type == SDL_MOUSEBUTTONDOWN){
			if(start.mouse_inside(mX, mY)){
				if(ev.button.button == SDL_BUTTON(SDL_BUTTON_LEFT)){
					state = GameState::Playing;
				}
			}
			if(option.mouse_inside(mX, mY)){
				if(ev.button.button == SDL_BUTTON(SDL_BUTTON_LEFT)){
					// options menu.
				}
			}		
			if(quit.mouse_inside(mX, mY)){
				if(ev.button.button == SDL_BUTTON(SDL_BUTTON_LEFT)){
					if(state == GameState::Menu)
					window->set_should_close(true);
					else
					state == GameState::Menu;
				}
			}
		}
	}
	if(state == GameState::Playing){
		em.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		if(!p.death_check()){
			p.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), em);
			pp->get()->setFade(false);
		}
		else{
			pp->get()->setFade(true);
			p.DeathAnimation(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), state);
			pp->get()->setDt(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
			
		}
	}else{
		start.update(mX, mY);
		option.update(mX, mY);
		quit.update(mX, mY);
		pp->get()->setFade(false);
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

float camX=0;
float camY=0;
void Game::draw(){
	ctx->clearColor(0.0, 0.0, 0.1f, 0.0);
	ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
	ctx->viewport(0, 0, w, h);
	ctx->enableAlpha();
	pp->begin();
		ls->use();
		view = glm::mat4();
	if(state == GameState::Playing || state == GameState::Pause){
		ls->setTex(0);
		if(state == GameState::Pause){
			tm.get_tex("ui-menu")->bind();
			ls->setTextured(true);	
			sb->draw(Vec2(0+100, h/2.0f - 161*2), Vec4(0, 310.0f/512.0f, 250.0f/512.0f, 471.0f/512.0f), Vec2(251*2, 161*2), Vec4(1.0));
			sb->draw(start.getPos(), start.getUvs(), start.getSize(), Vec4(start.getColor().x(), start.getColor().y(), start.getColor().z(), 1.0));
			sb->draw(option.getPos(), option.getUvs(), option.getSize(), Vec4(option.getColor().x(), option.getColor().y(), option.getColor().z(), 1.0));
			sb->draw(quit.getPos(), quit.getUvs(), quit.getSize(), Vec4(quit.getColor().x(), quit.getColor().y(), quit.getColor().z(), 1.0));
			sb->render();
		}
		for(int i = 0; i < 10; ++i){
			ls->setLight(i, lights[i]);
		}
		sb->draw(Vec2(0),Vec4(0),Vec2(5000, 5000), Vec4(0.1, 0.1, 0.1, 1.0));
		ls->setTextured(false);
		sb->render();
		ls->setTextured(true);
		tm.get_tex("wall")->bind();
		em.draw_blocks( *sb );

		ls->setTextured(false);
		em.draw_jumping_enemies(*sb);
		em.draw_basic_enemies(*sb);

		ls->setTextured(true);
		tm.get_tex("player")->bind();
		sb->draw(p.getPos(), p.getUvs(), p.getSize(), Vec4(p.getColor().r(), p.getColor().g(), p.getColor().b(), 1.0));
		sb->render();

		camX = -p.getPos().x() + w/2.0f;
		camY = -p.getPos().y() + h/2.0f;

		if(camX < -2280+w){
			camX = -2280+w;
		}

		view = glm::translate(view, glm::vec3(camX,camY,0));
	}else{
		pp->get()->setFade(false);
		ls->setTex(0);
		ls->setTextured(false);
		sb->draw(Vec2(-1000), Vec4(0), Vec2(50000), Vec4(0.09, 0.043, 0.1, 1.0));
		sb->render();
		ls->setLight(0, Light(7000, Vec3(0.0, 0.0, 0.5), Vec2(0)));
		ls->setLight(1, Light(7000, Vec3(0.5, 0.0, 0.0), Vec2(w, 0)));

		tm.get_tex("ui-menu")->bind();
		ls->setTextured(true);	
		sb->draw(Vec2(0+100, h/2.0f - 161*2), Vec4(0, 310.0f/512.0f, 250.0f/512.0f, 471.0f/512.0f), Vec2(251*2, 161*2), Vec4(1.0));
		sb->draw(start.getPos(), start.getUvs(), start.getSize(), Vec4(start.getColor().x(), start.getColor().y(), start.getColor().z(), 1.0));
		sb->draw(option.getPos(), option.getUvs(), option.getSize(), Vec4(option.getColor().x(), option.getColor().y(), option.getColor().z(), 1.0));
		sb->draw(quit.getPos(), quit.getUvs(), quit.getSize(), Vec4(quit.getColor().x(), quit.getColor().y(), quit.getColor().z(), 1.0));
		sb->render();
	}
		ls->unuse();
	pp->end();
	ls->setView(view);
	window->refresh();
}
