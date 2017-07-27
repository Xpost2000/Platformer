#ifndef PLAYER_H
#define PLAYER_H
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "Block.h"
class BasicEnemy;
class Player{
	public:
		Player(const Player& other) = default;
		Player(){}
		Player(Vec2 pos, Vec2 size, Vec2 velocity , Vec4 color)
		: pos(pos), size(size), velocity(velocity), color(color){
		}
		void update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be);
		Vec2 getPos() { return pos; }
		Vec2 getVelocity() { return velocity; }
		Vec2 getSize() { return size; }
		Vec4 getColor() { return color; }
	private:
		int health = 100;
		float jump_delay = 10;
		bool onGround = false;
		Vec2 pos;
		Vec2 velocity;
		Vec2 size;
		Vec4 color;
};
#endif
