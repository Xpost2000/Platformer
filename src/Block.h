#ifndef BLOCK_H
#define BLOCK_H
#include "Entity.h"
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"

// namespace to store identification types for the blocks.
// for now we have basic identifications for 3 basic types.
// I honestly have no idea how else it would work.
namespace BlockTypes{
	const int Floor = 1;
	const int Wall = 2;
	const int Ceiling = 3;
};
// This is a struct. pretty much.
class Block : public Entity{
	public:
		Block(Vec2 pos, Vec2 size, Vec4 color=Vec4(0.2), int type = BlockTypes::Floor)
		 : Entity(pos, size, Vec2(0), color){
			switch(type){
				// calculate the uvs based on where it is on a texture atlas.
				case BlockTypes::Floor:
					break;
				case BlockTypes::Wall:
					break;
				case BlockTypes::Ceiling:
					break;
				default:
					break;
			}	
		}
};
#endif
