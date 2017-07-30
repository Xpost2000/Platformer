#ifndef GAME_H
#define GAME_H
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
#include "LightShader.h"
#include "Postprocessor.h"

class Game{
	public:
		Game();
		~Game();
		void run();
	private:
		void update();
		void draw();
	private:
		bool active = true;
		SDL_Window* win = nullptr;
		SDL_Event ev;
		std::shared_ptr<ParticleRenderer> pr = nullptr;
		std::shared_ptr<SpriteBatcher> sb = nullptr;
		std::shared_ptr<LightShader> ls = nullptr;
		std::shared_ptr<PostProcessor> pp = nullptr;
		ptrs::ImageTexture player_texture;
		glm::mat4 view=glm::mat4(), proj=glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
		ptrs::IDevice ctx = nullptr;
};

#endif
