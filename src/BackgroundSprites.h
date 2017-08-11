#ifndef BACKGROUND_H
#define BACKGROUND_H
/*
 * Defines properties for things that appear in the background
 */
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "Block.h"
	
//TODO: Calculate UVs based on the block type it is.
//I guess a todo is to also add in the types. lol
struct BackgroundBlock{
	public:
		Vec4 getUvs(){
			return Vec4(0);
		}
		BackgroundBlock(){}
		BackgroundBlock(Vec2 pos, Vec2 size, Vec4 color, Vec2 scrollFactor)
		: pos(pos), size(size), color(color), scrollFactor(scrollFactor){
		}
		Vec2 pos;
		Vec2 size;
		Vec4 color;
		Vec2 scrollFactor;
};
struct BackgroundBlockStatic{
	public:
		Vec4 getUvs(){
			return Vec4(0);
		}
		BackgroundBlockStatic(){}
		BackgroundBlockStatic(Vec2 pos, Vec2 size, Vec4 color)
		: pos(pos), size(size), color(color){
		}
		Vec2 pos;
		Vec2 size;
		Vec4 color;
};
#endif
