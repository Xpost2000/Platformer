#ifndef PLAYER_H
#define PLAYER_H
#include "gravity.h"
#include <vector>
#include "Progressor.h"
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "direction.h"
#include "Block.h"
#include "Entity.h"
#include "GameState.h"
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
#include <memory>
#include "FreeTypeText.h"
class Player : public Entity{
	public:
		Player(const Player& other) = default;
		Player(){}
#ifndef EDITOR_BUILD
		Player(TextRenderer* ren, Vec2 pos, Vec2 size, Vec2 velocity , Vec4 color)
	 	: Entity(pos, size, velocity, color), ren(ren)	{
			set_aabb(Vec2(pos.x()+15, pos.y()+5), Vec2(40, 65));
			reposition_aabb();
			calculate_uvs();
		}
#else
		Player( Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color )
		: Entity(pos, size, velocity, color){
			magic=PLAYER;
			calculate_uvs();
		}
#endif
		void update(float dt, EntityManager& em);
		void update(float dt, std::vector<Block> &blocks, std::vector<BasicEnemy>& be, std::vector<JumpingEnemy>& je, Progressor& p);
		bool death_check(){ if(health < 0){ kill(); } return dead; }
		bool DeathAnimation( float dt, GameState& gs ) {
			if(color.a() > 0.0f){
				color.r() -= dt/2;
				color.g() -= dt/2;
				color.b() -= dt/2;
				color.a() -= dt/2;
				return false;
			}else{
			//	gs = GameState::Menu;
				color = Vec4(1.0);
				revive();

				return true;
			}
		}
		void kill(){ dead = true; pState = PlayerState::DEAD; }
		void revive(){ dead = false; health=100;}
		void set_input( bool i ) { input_allowed = i; }
		int score=0;
		// for da future
		int coins=0;
		int lives=3;
	private:
		bool input_allowed=1;
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
		TextRenderer* ren=nullptr;
		Direction playerDir=Direction::RIGHT;
		PlayerState pState=PlayerState::STANDING;
};
#endif
