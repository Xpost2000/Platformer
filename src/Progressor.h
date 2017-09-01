#ifndef PROGRESSOR_H
#define PROGRESSOR_H
#include "Entity.h"
#include "Block.h"
class Progressor : public Entity{
	public:
		Progressor(){}
		Progressor(const Progressor&) = default;
		Progressor(Vec2 pos, Vec2 size, Vec4 color)
		:Entity(pos, size, Vec2(0), color){
			magic =PROGRESSOR;
		}
		Vec4 getUvs(){
			return Block::get_uv_from_type(BlockTypes::Exit);
		}
		// makes no sense but I like morrowind so this is
		// a thing.
		void mark() { proceed=true; }
		void recall() { proceed=false; }
		bool can_go_next_level() { return proceed; }
	private:
		bool proceed=false;
};
#endif
