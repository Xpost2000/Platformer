/*
 * This class will just make basic enemies.
 * But for now just zombie like AI that only walks
 * around and turns the other direction if it touches something.
 */
#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H
#include "Block.h"
#include "RandomNumberGenerator.h"
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
// #include "Player.h"
class BasicEnemy{
	public:
		BasicEnemy(){}
		BasicEnemy(const BasicEnemy& other) = default;
		BasicEnemy(Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color)
		: pos(pos), size(size), velocity(velocity), color(color){
		}
		void update(float dt, std::vector<Block>& blocks);
		Vec2 getPos(){ return pos; }
		Vec2 getVelocity(){ return velocity; }
		Vec2 getSize(){ return size; }
		Vec4 getColor(){ return color; }
		bool isDead() { return dead; }
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
		void kill() { dead = true; }
	private:
		bool onGround;
		bool dead=0;
		// 1 in 4 chance to jump every frame.
		Vec2 pos;
		Vec2 velocity;
		Vec2 size;
		Vec4 color;
};
#endif
