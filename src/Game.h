#ifndef GAME_H
#define GAME_H
#include "LevelList.h"
#include "Config.h"
#include <iostream>
#include "ClockTimer.h"
#include "mat4.hpp"
#include "ParticleRenderer.h"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"
#include "DefaultShader.h"
#include "SpriteBatcher.h"
#include "RandomNumberGenerator.h"
#include "ParticleGenerator.h"
#include "EntityManager.h"
#include "LightShader.h"
#include "uiButton.h"
#include "Postprocessor.h"
#include "Window.h"
#include "TextureManager.h"
#include "GameState.h"
#include "GameCamera.h"
#include <array>
#include "BasicEnemy.h"
#include "JumpingEnemy.h"
#include "Block.h"
#include "Player.h"
#include "Level.h"

/*
 * 
 * TODO: Refactor all of this code
 * 	 cause it's starting to get very messy.
 *
 */
class Game{
	public:
		Game();
		// I need the editor to be able to essentially
		// force load a level so I'm going to add a few command line
		// arguments to allow this.
		Game(int argc, char** argv);
		Game(Game& other) = default;
		~Game();
		void run();
	private:
		void update();
		void draw();
		void parse_cmd(int argc, char** argv);
		void init();
		float w ;
		float h ;
		std::string game_name;
		bool initalized=false;
		// I need it to be like this cause I initalize it in the cpp file.
	private:
		uiButton start;
		uiButton option;
		uiButton quit;
		uiButton credits;
	private:
		GameState state = GameState::Menu;
		Config cfg;
		LevelListFile lst;
		GameCamera gc;
		EntityManager em;
		TextureManager tm;
		std::shared_ptr<Window> window = nullptr;
		SDL_Event ev;
		std::shared_ptr<ParticleRenderer> pr = nullptr;
		std::shared_ptr<SpriteBatcher> sb = nullptr;
		std::shared_ptr<LightShader> ls = nullptr;
		std::shared_ptr<PostProcessor> pp = nullptr;
		int currentLevel=0;
	public:
		// I need to hack some stuff in.
		std::vector<Level> levels;
	private:
		glm::mat4 proj;
		float amnt;
		ptrs::IDevice ctx = nullptr;
};

#endif
