#ifndef PLAYER_H
#define PLAYER_H
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "Block.h"
#include "Entity.h"
class BasicEnemy;
class JumpingEnemy;
class Player : public Entity{
	public:
		Player(const Player& other) = default;
		Player(){}
		Player(Vec2 pos, Vec2 size, Vec2 velocity , Vec4 color)
	 	: Entity(pos, size, velocity, color)	{
		}
		void update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be, std::vector<JumpingEnemy>& je);
		bool death_check(){ return health < 0; }
	private:
		void collide_blocks( float dt, std::vector<Block>& blocks );
		void floaty_jump(float dt);
		void move_left(float dt);
		void move_right(float dt);
		void jump(float dt);
		int health = 100;
		float jump_delay = 10;
		bool onGround = false;
};
#endif
