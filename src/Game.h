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

class Game{
	public:
		Game();
		~Game();
		void run();
	private:
		void update();
		void draw();
		float w ;
		float h ;
		std::string game_name;
	private:
		uiButton start;
		uiButton option;
		uiButton quit;
		uiButton credits;
	private:
		GameState state = GameState::Menu;
		Config cfg;
		LevelListFile lst;
		EntityManager em;
		TextureManager tm;
		std::shared_ptr<Window> window = nullptr;
		SDL_Event ev;
		std::shared_ptr<ParticleRenderer> pr = nullptr;
		std::shared_ptr<SpriteBatcher> sb = nullptr;
		std::shared_ptr<LightShader> ls = nullptr;
		std::shared_ptr<PostProcessor> pp = nullptr;
		glm::mat4 view=glm::mat4(), proj;
		ptrs::IDevice ctx = nullptr;
};

#endif
