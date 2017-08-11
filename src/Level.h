#ifndef LEVEL_H
#define LEVEL_H
#include "LightStruct.h"
#include <vector>
#include <array>
#include "Player.h"
#include "Block.h"
#include "EntityManager.h"
#include <string>
// I'm going to load a file and upload the data to
// structs stored within the level.
// when needed the game will request to copy the data
// to "load" the level.
class Level{
	public:
		Level ( const Level& other ) = default;
		Level(){}
		Level(std::string path);
		void load( Player& p, EntityManager& em, std::array<Light, 10>& light){
			p.setPos(playerSpawnPos);
			em = this->em;
			loaded = true;
			light = lights;
		}
		bool loaded=false;
	private:
		Vec2 playerSpawnPos;
		EntityManager em;
		std::array<Light, 10> lights;

};

#endif
