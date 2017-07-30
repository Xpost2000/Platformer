/*
 * These guys can jump randomly
 */
#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H
#include "Entity.h"
#include "Block.h"
#include "RandomNumberGenerator.h"
#include "gravity.h"
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "BasicEnemy.h"
#include "vec4.hpp"
// #include "Player.h"
class JumpingEnemy : public BasicEnemy{
	public:
		JumpingEnemy(){}
		JumpingEnemy(const JumpingEnemy& other) = default;
		JumpingEnemy(Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color)
			: BasicEnemy(pos, size, velocity, color){
		}
		void update(float dt, std::vector<Block>& blocks);
	private:
};
#endif
