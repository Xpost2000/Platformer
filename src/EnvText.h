#ifndef ENV_TEXT_STRUCT_H
#define ENV_TEXT_STRUCT_H

/*
 * This kind of text is as it sounds.
 * It's text on an environment
 */
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include <string>
struct EnvironmentText{
	public:
		EnvironmentText( Vec2 pos, Vec3 color, float scale , const std::string& str ) : pos(pos), color(color), scale(scale), str(str){
		}
		Vec2 pos;
		Vec3 color;
		float scale;
		std::string str;
};

#endif
