#ifndef BLOCK_H
#define BLOCK_H
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
// This is a struct. pretty much.
class Block{
	public:
		Block(Vec2 pos, Vec2 size, Vec4 color=Vec4(0.2))
		:pos(pos), size(size), color(color){
		}
		Vec2 getPos() { return pos; }
		Vec2 getSize() { return size; }
		Vec4 getColor() { return color; }
	private:
		Vec2 pos;
		Vec2 size;
		Vec4 color;
};
#endif
