#include "Level.h"
#include <exception>
#include <fstream>

#define FOUND_LIMITS 0
#define FOUND_PROGRESSOR 1
#define FOUND_PSPAWN 2
Level::Level(std::string path){
	// just clean init everything first;
	for(auto& l : lights) { l = Light(); }
	std::ifstream file(path.c_str());
	std::string token;
	bool flags[3]={false};
	try{
	while(file >> token){
		if(token == "camera_limits"){
			if(flags[FOUND_LIMITS]){ std::cerr << "WARNING: MULTIPLE CAMERA LIMITS FOUND. SKIPPING\n"; break; }
			float lX=0, lY=0, hX=0, hY=0;
			file >> lX;
			file >> lY;
			file >> hX;
			file >> hY;
			flags[FOUND_LIMITS] = true;
			// camera == Camera( lowerLimits(lX, lY), Limits(hX, hY) );
		}
		if(token == "block"){
			float w=0, h=0, x=0, y=0, r=0, g=0, b=0; int type=0;
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
			if(flags[FOUND_PROGRESSOR]){ std::cerr << "WARNING: MULTIPLE PROGRESSORS FOUND. SKIPPING\n"; break; }
			float w=0, h=0, x=0, y=0, r=0, g=0, b=0;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			flags[FOUND_PROGRESSOR] = true;
			em.set_progressor(Progressor(Vec2(x, y), Vec2(w, h), Vec4(r, g, b, 1.0)));
		}
		if(token == "bgrnd"){
			float w=0, h=0, x=0, y=0, sx=0, sy=0 , r=0, g=0, b=0;
			int type=0;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> sx;
			file >> sy;
			file >> r;
			file >> g;
			file >> b;
			file >> type;
			em.create_block(BackgroundBlock(Vec2(x,y),Vec2(w,h),Vec4(r, g, b, 1.0), Vec2(sx, sy), type));
		}
		if(token == "bgrnd-static"){
			float w=0, h=0, x=0, y=0, r=0, g=0, b=0;
			int type=0;
			file >> w;
			file >> h;
			file >> x;
			file >> y;
			file >> r;
			file >> g;
			file >> b;
			file >> type;
			em.create_block(BackgroundBlockStatic(Vec2(x,y),Vec2(w,h),Vec4(r, g, b, 1.0), type));
		}
		if(token == "light"){
			// I usually declare the variables in the order they are supposed to be used.
			int index;
			float x=0, y=0;
			float power=0;
			float r=0, g=0, b=0;
			file >> index;
			if(index > 9 || index < 0){ throw std::range_error("MAX INDEX FOR LIGHTS IS 10(from the zeroth index it's actually 9). PROVIDED IN FILE EXCEEDS IT."); break; }
			file >> x;
			file >> y;
			file >> power;
			file >> r;
			file >> g;
			file >> b;
			lights[index]=Light(power, Vec3(r, g, b), Vec2(x, y));
		}
		if(token == "player_spawn"){
			if(flags[FOUND_PSPAWN]){ std::cerr << "WARNING: MULTIPLE PLAYERS SPAWNS FOUND. SKIPPING\n"; break; }
			file >> playerSpawnPos.x();
			file >> playerSpawnPos.y();
			flags[FOUND_PSPAWN] = true;
		}
	}
	}catch(const std::exception& e){
		std::cerr << "EXCEPTION CAUGHT:\n";
		std::cerr << "Exception Thrown : " << e.what() << std::endl;
		exit(-1);
	}
}
