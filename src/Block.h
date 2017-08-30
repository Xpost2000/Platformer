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
	const int BasicBox = 1;
	const int FlatColor = 2;
	const int Box = 3;
	const int Canister = 4;
	const int ControlPanel = 5;
	const int DoubleDoors = 6;
	const int Exit = 7;
	const int ExitSign = 8;
	const int Floor = 9;
	const int KeyPad = 10;
	const int Pipe = 11;
	const int RetinaScanner=12;
	const int UniqueDoor = 13;
	const int WallTile = 14;
	const int WarningSign = 15;
}	
const int KILLZONE_BLOCK =16;
// This is a struct. pretty much.
class Block : public Entity{
	public:
		// I know a block cannot really "die", but I can use it as a flag for active ness..
		// TODO: Replace the UVs for the new finalized tile map.
		void revive(){dead=false;}
		void kill(){dead=true;}
		// This is if you wish to draw a "Block" I'm just using it for the background which is a flat color
		// Only doing to avoid minor uniform changing. It's not really that substatial
		static Vec4 get_uv_from_type(int type){
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
					return Vec4(NW(44), NH(27), NW(44+15), NH(44+15));
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
					return Vec4(NW(0), NH(0), NW(25), NH(25));
				break;
				case BlockTypes::WarningSign:
					return Vec4(NW(22), NH(27), NW(42), NH(47));
				break;
				default:
					break;
			}
		}

		Vec4 getUvs(){
#ifdef OLD_UV_SHEET
			/*
			 * To future people and future me when I re read this at some point.
			 * I know I know, there is a simple expression to calculate the UVs based on
			 * the rows and columns but I believe it sadly only works if all the sub images
			 * are all the same size. Eh
			 */
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
#else
			// replace the borken macro with lambda functor objects cause it will work
//define NW(x) x / 128
//#define NH(x) x / 128
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
					return Vec4(NW(44), NH(27), NW(44+15), NH(44+15));
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
					return Vec4(NW(0), NH(0), NW(25), NH(25));
				break;
				case BlockTypes::WarningSign:
					return Vec4(NW(22), NH(27), NW(42), NH(47));
				break;
				default:
					break;
			}
#endif
		}
		Block(const Block& other) = default;
		Block() {}
		Block(Vec2 pos, Vec2 size, Vec4 color=Vec4(0.2), int type = BlockTypes::Floor)
		 : Entity(pos, size, Vec2(0), color), type(type){
			 magic=BLOCK;
		}
		int& get_type() { return type; }
	protected:
	int type;
};
#endif
