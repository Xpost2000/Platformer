#include "Level.h"
#include <fstream>

Level::Level(std::string path){
	std::ifstream file(path.c_str());
	std::string token;
	while(file >> token){
		if(token == "block"){
			int w, h, x, y, r, g, b, type;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			file >> type;
			em.create_block(Block(Vec2(x, y), Vec2(w, h), Vec4(r, g, b, 1.0), type));
	//		blocks.push_back(Block(Vec2(x, y), Vec2(w, h), Vec4(r, g, b, 1.0), type));
		}
		if(token == "player_spawn"){
			file >> playerSpawnPos.x();
			file >> playerSpawnPos.y();
		}
	}
}
