#ifndef PLAYER_H
#define PLAYER_H
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
struct block{
	block(Vec2 pos, Vec2 size) : pos(pos), size(size){}
	Vec2 pos;
	Vec2 size;
};
class Player{
	public:
		Player(const Player& other) = default;
		Player(){}
		Player(Vec2 pos, Vec2 size, Vec2 velocity , Vec4 color)
		: pos(pos), size(size), velocity(velocity), color(color){
		}
		void update(float dt, std::vector<block> &blocks);
		// make everything public for now.
		float jump_delay = 10;
		bool onGround = false;
		Vec2 pos;
		Vec2 velocity;
		Vec2 size;
		Vec4 color;
};
#endif
