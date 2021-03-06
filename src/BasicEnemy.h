/*
 * This class will just make basic enemies.
 * But for now just zombie like AI that only walks
 * around and turns the other direction if it touches something.
 *
 *  I could maybe create sub classes of the starting types by
 *  just updating them differently on the magic number they spawn with.
 *
 */
#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H
#include "Entity.h"
#include "Block.h"
#include "RandomNumberGenerator.h"
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
#include "direction.h"
enum class EnemyState{
	JUMPING,
	STANDING,
	WALKING,
	DEAD,
	HURT,
	FALLING
};
class BasicEnemy : public Entity{
	public:
		BasicEnemy(){}
		BasicEnemy(const BasicEnemy& other) = default;
		BasicEnemy(Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color)
			: Entity(pos, size, velocity, color){
		}
		virtual void update(float dt, std::vector<Block>& blocks);
		// bool used to return whether finished or not.
		bool DeathAnimation( float dt ) {
			if(color.a() > 0.0f){
				color.r() -= dt/2;
				color.g() -= dt/2;
				color.b() -= dt/2;
				color.a() -= dt/2;
				return false;
			}else{
				return true;
			}
		}
		void kill(){dead = true; eState = EnemyState::DEAD;}
		void revive(){dead = false;}
	protected:
		EnemyState eState;
		Direction dir;
		// 1 / 15 chance roughly.
		bool onGround;
};
#endif
