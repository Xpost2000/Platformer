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
		// I know a block cannot really "die", but I can use it as a flag for active ness..
		void revive(){dead=false;}
		void kill(){dead=true;}
		Vec4 getUvs(){
			switch(type){
				case BlockTypes::Floor:
					return Vec4(0, 31/64.0f, 30/64.0f, 61/64.0f);
					break;
				case BlockTypes::Wall:
					return Vec4(0, 0, 30/64.0f, 30/64.0f);
					break;
				case BlockTypes::Ceiling:
					return Vec4(31/64.0f, 0, 61/64.0f, 30/64.0f);
					break;
				default:
					break;
			}
		}
		Block(const Block& other) = default;
		Block(Vec2 pos, Vec2 size, Vec4 color=Vec4(0.2), int type = BlockTypes::Floor)
		 : Entity(pos, size, Vec2(0), color), type(type){
		}
	private:
	int type;
};
#endif
