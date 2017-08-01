#ifndef LEVEL_H
#define LEVEL_H
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
		void load( Player& p, EntityManager& em){
			p.setPos(playerSpawnPos);
			em = this->em;
		}
	private:
		Vec2 playerSpawnPos;
		EntityManager em;
};

#endif
