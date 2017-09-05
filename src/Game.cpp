#include "Game.h"
#include "Sound.h"

// I'm likely going to stre a different vector for different enemy types.
// I used it for animation time.

std::array<Light, 10> lights{
	Light(),
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
Game::Game(int argc, char** argv){
	// no arguments (except for the default argument 0 which is the program name)
	parse_cmd(argc, argv);
	cfg.read_config();
	init();
}
Game::Game(){
	cfg.read_config();
	w = cfg.get_window_width();
	h = cfg.get_window_height();
	init();	
	std::cout << "\n\nEntries in the level list\n";
	lst.read(cfg.get_lvl_list_dir() + cfg.get_lvl_list_file());
	for( auto &ent : lst.entries ){
		std::cout << ent << std::endl;
		levels.push_back(Level(ent));
	}
}
Game::~Game(){
	Sound::free_memory();
	SDL_Quit();
}
void Game::run(){
	if(initalized){
	while(!window->should_close()){
		update();
		draw();
		}
	}else{ exit(0); }
}
// package this into a mouse struct class.
int mX;
int mY;
// this is essentially basic initalization in general.
void Game::init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	Sound::init();
	start = uiButton(Vec2(0+100, h/2.0f + 50), Vec2(300, 60), Vec3(1.0), Vec3(1.0, 0.0, 0.0), ButtonType::Start);
	option = uiButton(Vec2(0+100, h/2.0f + 120), Vec2(300, 60), Vec3(1.0), Vec3(0.0, 1.0, 0.0), ButtonType::Options);
	quit = uiButton(Vec2(0+100, h/2.0f + 180), Vec2(300, 60), Vec3(1.0), Vec3(0.0, 0.0, 1.0), ButtonType::Quit);
	game_name = cfg.get_game_name();
	std::cout << "Game Name :: " << game_name << std::endl;
	std::cout << "Level List Directory ::" << cfg.get_lvl_list_dir() + cfg.get_lvl_list_file() << std::endl;
	std::cout << "Texture Files Directory ::" << cfg.get_texture_dir() << std::endl;
	std::cout << "Level Files Directory ::" << cfg.get_level_dir() << std::endl;
	std::cout << "Sound Files Directory ::" << cfg.get_sounds_dir() << std::endl;
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
	if(GLEW_VERSION_3_3){
	}else{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error : OpenGL 3.3 not supported", "Please update your video drivers.", NULL);
		exit(-1);
	}
	pr = std::make_shared<ParticleRenderer>(ctx);
	sb = std::make_shared<SpriteBatcher>(ctx);
	ls = std::make_shared<LightShader>(ctx);
	pp = std::make_shared<PostProcessor>(ctx, w, h);
	btr = std::make_shared<BitmapTextRenderer>(ctx);
	ftr = std::make_shared<TextRenderer>(ctx, "textures//ui//ocr.ttf");
	p = Player(ftr.get(),Vec2(300, 300), Vec2(73, 73), Vec2(100), Vec4(1.0, 1.0, 1.0, 1.0));
	tm.add_texture("tiles", "textures//tiles.png", ctx);
	tm.add_texture("player", "textures//test_player.png", ctx);
	tm.add_texture("ui-menu", "textures//ui//ui_atlas.png", ctx);
	tm.add_texture("coin", "textures//coin_base.png", ctx);
	Sound::load_sound(cfg.get_sounds_dir()+std::string("beep.wav"), "beep");
	Sound::load_sound(cfg.get_sounds_dir()+std::string("jump.wav"), "jump");
	Sound::load_sound(cfg.get_sounds_dir()+std::string("progressor.wav"), "nextLevel");
	Sound::load_music(cfg.get_sounds_dir()+std::string("main.wav"), "music");
	gc = GameCamera(Vec2(0, 0), Vec2(w, h), Vec2(-3000, -3000), Vec2(3000, 3000));
	ls->setProj(proj);
	initalized =true;
}
void Game::update(){
	ClockTimer::Tick();
	SDL_GetMouseState(&mX, &mY);
	if(state == GameState::Playing || state == GameState::Progression){
		if(levels[currentLevel].loaded == false){
			levels[currentLevel].load(p, em, lights);
		}
		if(state == GameState::Playing && levels[currentLevel].loaded){
		Sound::play_music("music", 1);
		em.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		if(!p.death_check()){
			p.update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), em);
			pp->get()->setFade(false);
			amnt = 1;
		}
		else{
			pp->get()->setFade(true);
			if(p.DeathAnimation(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), state)){
				levels[currentLevel].loaded=false;
				p.lives--;
			}
			amnt -= ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS)/2;
			pp->get()->setDt(amnt);			
		}
		}
		if(em.get_progressor().can_go_next_level()){
			if(levelDelay <= 0){
			currentLevel++;
			em.get_progressor().recall();
			draw_game = true;
			levelDelay=100;
			p.set_input(true);
			}else{
				levelDelay-= ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS)*45;
				draw_game = false;
				p.set_input(false);
			}
		}
		if(p.lives <= 0){
			p.score = 0;
			p.coins = 0;
			p.lives = 3;
			state = GameState::Menu;
			gc.get_matrix() = glm::mat4();
		}
	}else{
		start.update(mX, mY);
		option.update(mX, mY);
		quit.update(mX, mY);
		Sound::stop_music();
		pp->get()->setFade(false);
	}
	while(SDL_PollEvent(&ev)){
		if(ev.type==SDL_QUIT){
			window->set_should_close(true);
		}
		//DEBUGGING PURPOSES
		if(ev.key.keysym.sym == SDLK_RETURN){
			if(state == GameState::Intro){
				if(cutSceneLength > 0){
					cutSceneLength=-1;
				}
			}
		}
		if((ev.type == SDL_MOUSEBUTTONDOWN)){
			if(start.mouse_inside(mX, mY)){
				if(state == GameState::Menu || state == GameState::Pause){
					state = GameState::Intro;
				}
			}
			if(option.mouse_inside(mX, mY)){
					// options menu.
			}		
			if(quit.mouse_inside(mX, mY)){
				if(state == GameState::Menu)
				window->set_should_close(true);
				else
				state = GameState::Menu;
			}
		}
	}
}



void Game::draw(){
	ctx->clearColor(0.0, 0.0, 0.0, 1.0);
	ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
	ctx->viewport(0, 0, w, h);
	ctx->enableAlpha();
	pp->begin();
	if(state == GameState::Playing || state == GameState::Progression){
		for(int i = 0; i < 10; ++i){
			ls->setLight(i, lights[i]);
		}
		// this is herr sky.
		ls->use();
		ls->setTex(0);
		ls->setTextured(true);
		tm.get_tex("tiles")->bind();
		sb->draw(Vec2(-5000), Vec4(Block::get_uv_from_type(BlockTypes::FlatColor)), Vec2(10000), Vec4(0.1, 0.1, 0.1, 1.0));
		em.draw_background_props( gc.getPos(), *sb );
		em.draw_progressor(*sb);
		em.draw_blocks( *sb );
		em.draw_text( *ftr );
		tm.get_tex("coin")->bind();
		em.draw_coins( *sb );
		ls->setTextured(false);
		em.draw_jumping_enemies(*sb);
		em.draw_basic_enemies(*sb);

		ls->setTextured(true);
		tm.get_tex("player")->bind();
		sb->draw(p.getPos(), p.getUvs(), p.getSize(), Vec4(p.getColor().r(), p.getColor().g(), p.getColor().b(), 1.0f));
		sb->render();
		ls->setTextured(false);
		if(!draw_game){
			// there is an issue of the player falling through the world due to frame
			// issues. ( The framerate is absurdly high and it ends up skipping or pretty much overpowering my game's
			// updating )
			tm.get_tex("tiles")->bind();
			sb->draw( Vec2(-5000), Vec4(Block::get_uv_from_type(BlockTypes::FlatColor)), Vec2(20000), Vec4(0, 0, 0, 1) );
			sb->render();
		}

		ftr->render("Lives : " + std::to_string(p.lives), glm::vec2(30, 00), 0.5, glm::vec3(1));
		ftr->render("Score : " + std::to_string(p.score), glm::vec2(30, 50), 0.5, glm::vec3(1));
		ftr->render("Coins : " + std::to_string(p.coins), glm::vec2(500, 000), 0.5, glm::vec3(1));
		ftr->render("Sample Text" , glm::vec2(p.getPos().x(), p.getPos().y()), 0.2, glm::vec3(1), true);
		if(em.get_progressor().can_go_next_level() && levelDelay > 0){
			ftr->render("You have " + std::to_string(p.lives) + " Lives", glm::vec2(200, 330), 0.6,glm::vec3(0, 1, 0));
			ftr->render("Approaching next floor on ship...", glm::vec2(200, 300), 0.5, glm::vec3(1));
			state = GameState::Progression;
		}
		if(draw_game){
			state = GameState::Playing;
		}
		gc.update(p);
	}else if( state == GameState::Menu || state == GameState::Pause ){
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
		ftr->render("A game by Xpost 2000", glm::vec2(0, 0), 0.3, glm::vec3(1));
	}else if ( state == GameState::Intro ){
		if(cutSceneLength > 0){
			// Emerge epic cutscene :D
			ls->setTextured(false);
			sb->draw(Vec2(-1000), Vec4(0), Vec2(50000), Vec4(0));
			sb->render();
			if(cutSceneLength > CUTSCENE_LENGTH-100){
			ftr->render("Insert Story Mode Gibberish", glm::vec2(10, 300), 1.1, glm::vec3(1));
			ftr->render("*Totally Filler content with no significant contribution to story*\n2+2=fish.", glm::vec2(100, 400), 0.3, glm::vec3(1));
			}else if(cutSceneLength > 0){
				ftr->render("Page 2 of story mode gibberish", glm::vec2(10, 300), 0.8, glm::vec3(1));
				ftr->render("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nummus in Croesi divitiis obscuratur, pars est\ntamen divitiarum. Graece donan, Latine voluptatem vocant. Nulla erit controversia. Tu vero, inquam, ducas\nlicet, si sequetur; Quodsi ipsam honestatem undique pertectam atque absolutam. Respondent extrema\nprimis, media utrisque, omnia omnibus. Iam id ipsum absurdum, maximum malum neglegi. Duo Reges:\nconstructio interrete. Ergo in gubernando nihil, in officio plurimum interest, quo in genere peccetur. Quod\nautem in homine praestantissimum atque optimum est, id deseruit.",
						glm::vec2(30, 420), 0.3, glm::vec3(1));
			}
			cutSceneLength -= ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS)*45;
		}else{ cutSceneLength = CUTSCENE_LENGTH; state = GameState::Playing; }
	}
	ls->unuse();
	pp->end();
	ls->setView(gc.get_matrix());
	ftr->setMatrices( proj, gc.get_matrix() );
	window->refresh();
}

// I'm going to create a few tables containing data here for easy usage.
// I'm using a pair because all commands will have a short hand 
// representation and the standand representation.

// here's a convient macro
#define COMMAND(sh, cmd, desc) std::make_pair<std::pair<std::string, std::string>, std::string>(std::make_pair<std::string, std::string>(sh, cmd), desc)
/*
std::pair<std::string, std::string> command_strings[]={
	std::make_pair<std::string, std::string>("-h", "--help"),
	std::make_pair<std::string, std::string>("-v", "--version"),
	std::make_pair<std::string, std::string>("-fl", "--forceload_level"),
	std::make_pair<std::string, std::string>("-res", "--resolution")
};
*/
// I'm going to make a pair of a pair of strings and then a string
// because I'm using it like this
// (shortcut cmd, full cmd name), (description)
// TODO use an std array so I don't have to slightly change the for loop next time.
std::pair<std::pair<std::string, std::string>, std::string> command_strings[]={
	COMMAND("-h", "--help", "Shows you all command line arguments"),
	COMMAND("-v", "--version", "Shows you current software version"),
	COMMAND("-fl", "--forceload_level", "Forcefully load a level, ignoring the level list\n"),
	COMMAND("-res", "--resolution", "start the game at a set resolution"),
	COMMAND("-e", "--editor-run", "Only use if the editor runs this program, it is a combination of -v and -fl")
};

#define CALLBACK_CMD(name) [&](int &argc, char** argv , Game* instance)
std::function<void(int&, char**, Game*)> command_callbacks[]={
	CALLBACK_CMD("HELP"){
		std::cout << "List of accepted commands\n-----------------------------\n" << std::endl;
		for(auto& commands : command_strings){
			std::cout << commands.first.first << "\t" << commands.first.second << "\t" << commands.second << std::endl;
		}
		std::cout << "If you have questions about gameplay and or\nother things, please contact me at xpost2000cod@gmail.com\n" << std::endl;
		exit(0);
	},
	CALLBACK_CMD("VERSION"){
		std::cout << "I distribute this program under the zlib license" << std::endl;
		std::cout << "This game is in pre-alpha stage" << std::endl;
		exit(0);
	},
	CALLBACK_CMD("LOAD LEVEL"){
		std::cerr << "Please note levels loaded that have a progressor cannot go to the next level and will crash the program\n";
		instance->levels.push_back(Level(argv[++argc]));
//		instance->state = GameState::Playing;
	},
	CALLBACK_CMD("RESOLUTION"){
		instance->w = atoi(argv[++argc]);
		instance->h = atoi(argv[++argc]);
	},
	CALLBACK_CMD("EDITOR RUN FLAG"){
		command_callbacks[2](argc, argv, instance);
		command_callbacks[3](argc, argv, instance);
	}
};

void Game::parse_cmd(int argc, char** argv){
	// I keep going whilst there are still strings pretty much.
	std::string cmd_string;
	int argc_cur = 1;	
	for( ; argc_cur < argc; ++argc_cur ){
		cmd_string = argv[argc_cur];
		for( size_t i = 0; i < 5; ++i ){
			std::pair<std::string, std::string> cmd = command_strings[i].first;
			if(cmd_string == cmd.first || cmd_string == cmd.second){
				// the functions are made in order anyways.
				command_callbacks[i](argc_cur, argv, this);
			}
		}
	}
}
