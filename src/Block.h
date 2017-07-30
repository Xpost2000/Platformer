#ifndef BLOCK_H
#define BLOCK_H
#include "Entity.h"
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
// This is a struct. pretty much.
class Block : public Entity{
	public:
		Block(Vec2 pos, Vec2 size, Vec4 color=Vec4(0.2))
		 : Entity(pos, size, Vec2(0), color){
		}
};
#endif
