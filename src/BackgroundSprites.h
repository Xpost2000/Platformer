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
class BackgroundBlock : public Block{
	public:
		Vec4 getUvs(){
			auto NW = [&](float x) { return x / 128.0f; };
			auto NH = [&](float x) { return x / 128.0f; };
			switch(type){
				case BlockTypes::BasicBox:
					return Vec4(NW(0), NH(49), NW(10), NH(59));
				break;
				case BlockTypes::FlatColor:
					return Vec4(NW(0), NH(61), NW(1), NH(62));
				break;	
				case BlockTypes::Box:
					return Vec4(NW(12), NH(49), NW(22), NH(59));
				break;
				case BlockTypes::Canister:
					return Vec4(NW(44), NH(27), NW(44+15), NH(44+27));
				break;
				case BlockTypes::ControlPanel:
					return Vec4(NW(44), NH(44), NW(44+15), NH(44+15));
				break;
				case BlockTypes::DoubleDoors:
					return Vec4(NW(54), NH(0), NW(54+15), NH(15));
				break;
				case BlockTypes::Exit:
					return Vec4(NW(24), NH(49), NW(24+10), NH(49+10));
				break;
				case BlockTypes::ExitSign:
					return Vec4(NW(0), NH(0), NW(25), NH(25));
				break;
				case BlockTypes::Floor:
					return Vec4(NW(61), NH(17), NW(61+10), NH(17+10));
				break;
				case BlockTypes::KeyPad:
					return Vec4(NW(0), NH(27), NW(47), NH(20));
				break;
				case BlockTypes::Pipe:
					return Vec4(NW(61), NH(29), NW(71), NH(39));
				break;
				case BlockTypes::RetinaScanner:
					return Vec4(NW(27), NH(0), NW(27+25), NH(25));
				break;
				case BlockTypes::UniqueDoor:
					return Vec4(NW(71), NH(0), NW(71+15), NH(15));
				break;
				case BlockTypes::WallTile:
					return Vec4(NW(88), NH(0), NW(15+88), NH(15));
				break;
				case BlockTypes::WarningSign:
					return Vec4(NW(22), NH(27), NW(42), NH(47));
				break;
				default:
					break;
			}
		}
		BackgroundBlock(){}
		BackgroundBlock(Vec2 pos, Vec2 size, Vec4 color, Vec2 scrollFactor, int type)
		: Block(pos, size, color, type), scrollFactor(scrollFactor){
			magic=BGRNDBLOCK;
		}
		Vec2 scrollFactor;
};
class BackgroundBlockStatic : public Block{
	public:
		Vec4 getUvs(){
			auto NW = [&](float x) { return x / 128.0f; };
			auto NH = [&](float x) { return x / 128.0f; };
			switch(type){
				case BlockTypes::BasicBox:
					return Vec4(NW(0), NH(49), NW(10), NH(59));
				break;
				case BlockTypes::FlatColor:
					return Vec4(NW(0), NH(61), NW(1), NH(62));
				break;	
				case BlockTypes::Box:
					return Vec4(NW(12), NH(49), NW(22), NH(59));
				break;
				case BlockTypes::Canister:
					return Vec4(NW(44), NH(27), NW(44+15), NH(44+27));
				break;
				case BlockTypes::ControlPanel:
					return Vec4(NW(44), NH(44), NW(44+15), NH(44+15));
				break;
				case BlockTypes::DoubleDoors:
					return Vec4(NW(54), NH(0), NW(54+15), NH(15));
				break;
				case BlockTypes::Exit:
					return Vec4(NW(24), NH(49), NW(24+10), NH(49+10));
				break;
				case BlockTypes::ExitSign:
					return Vec4(NW(0), NH(0), NW(25), NH(25));
				break;
				case BlockTypes::Floor:
					return Vec4(NW(61), NH(17), NW(61+10), NH(17+10));
				break;
				case BlockTypes::KeyPad:
					return Vec4(NW(0), NH(27), NW(47), NH(20));
				break;
				case BlockTypes::Pipe:
					return Vec4(NW(61), NH(29), NW(71), NH(39));
				break;
				case BlockTypes::RetinaScanner:
					return Vec4(NW(27), NH(0), NW(27+25), NH(25));
				break;
				case BlockTypes::UniqueDoor:
					return Vec4(NW(71), NH(0), NW(71+15), NH(15));
				break;
				case BlockTypes::WallTile:
					return Vec4(NW(88), NH(0), NW(15+88), NH(15));
				break;
				case BlockTypes::WarningSign:
					return Vec4(NW(22), NH(27), NW(42), NH(47));
				break;
				default:
					break;
			}
		}
		BackgroundBlockStatic(){}
		BackgroundBlockStatic(Vec2 pos, Vec2 size, Vec4 color, int type)
		: Block(pos, size, color, type){
			magic=STBLOCK;
		}
};

#endif
