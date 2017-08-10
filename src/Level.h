#ifndef LEVEL_H
#define LEVEL_H
#include "LightStruct.h"
#include <vector>
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
		void load( Player& p, EntityManager& em, Light lights[10]){
			p.setPos(playerSpawnPos);
			em = this->em;
			loaded = true;
			lights = this->lights;
		}
		bool loaded=false;
	private:
		Vec2 playerSpawnPos;
		EntityManager em;
		Light lights[10]={Light()};
};

#endif
