#ifndef PLAYER_H
#define PLAYER_H
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "direction.h"
#include "Block.h"
#include "Entity.h"
class BasicEnemy;
class JumpingEnemy;

enum class PlayerState{
	WALKING,
	STANDING,
	JUMPING,
	FALLING,
	HURT,
	DEAD
};
class EntityManager;
class Player : public Entity{
	public:
		Player(const Player& other) = default;
		Player(){}
		Player(Vec2 pos, Vec2 size, Vec2 velocity , Vec4 color)
	 	: Entity(pos, size, velocity, color)	{
			set_aabb(Vec2(pos.x()+15, pos.y()+5), Vec2(40, 65));
		}
		void update(float dt, EntityManager& em);
		void update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be, std::vector<JumpingEnemy>& je);
		bool death_check(){ return health < 0; }
		void kill(){ dead = true; pState = PlayerState::DEAD; }
		void revive(){ dead = false; }
	private:
		void reposition_aabb(){ bb.pos.x() = pos.x()+15; bb.pos.y() = pos.y()+8; }
		void calculate_uvs();
		void print_state();
		void collide_blocks( float dt, std::vector<Block>& blocks );
		void floaty_jump(float dt);
		void move_left(float dt);
		void move_right(float dt);
		void jump(float dt);
		int health = 100;
		float jump_delay = 10;
		bool onGround = false;
		Direction playerDir;
		PlayerState pState;
};
#endif
