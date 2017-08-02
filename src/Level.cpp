#include "Level.h"
#include <fstream>

Level::Level(std::string path){
	std::ifstream file(path.c_str());
	std::string token;
	while(file >> token){
		if(token == "camera_limits"){
			float lX, lY, hX, hY;
			file >> lX;
			file >> lY;
			file >> hX;
			file >> hY;
			// camera == Camera( lowerLimits(lX, lY), Limits(hX, hY) );
		}
		if(token == "block"){
			float w, h, x, y, r, g, b, type;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			file >> type;
			em.create_block(Block(Vec2(x, y), Vec2(w, h), Vec4(r, g, b, 1.0), type));
		}
		if(token == "progressor"){
			float w, h, x, y, r, g, b;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			em.set_progressor(Progressor(Vec2(x, y), Vec2(w, h), Vec4(r, g, b, 1.0)));
		}
		if(token == "bgrnd"){
			float w, h, x, y, sx, sy , r, g, b;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> sx;
			file >> sy;
			file >> r;
			file >> g;
			file >> b;
			em.create_block(BackgroundBlock(Vec2(x,y),Vec2(w,h),Vec4(r, g, b, 1.0), Vec2(sx, sy)));
		}
		if(token == "bgrnd-static"){
			float w, h, x, y, r, g, b;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			em.create_block(BackgroundBlockStatic(Vec2(x,y),Vec2(w,h),Vec4(r, g, b, 1.0)));
		}
		if(token == "player_spawn"){
			file >> playerSpawnPos.x();
			file >> playerSpawnPos.y();
		}
	}
}
