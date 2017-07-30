#ifndef ENTITY_H
#define ENTITY_H
/*
 * Entity base class that stores common attributes.
 * ( honestly I should learn some other pattern so I avoid making
 * 	huge entity classes )
 */
#include <vector>
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"

class Block;
class Entity{
	public:
		Entity(){}
		Entity(const Entity& other) = default;
		Entity(Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color)
		: pos(pos), size(size), velocity(velocity), color(color){
		}
		virtual void update(float dt, std::vector<Block>& blocks){}
		Vec2 getPos(){ return pos; }
		Vec2 getVelocity(){ return velocity; }
		Vec2 getSize(){ return size; }
		Vec4 getColor(){ return color; }
		bool isDead() { return dead; }
		bool intersect( Entity &other )	{
			return ( pos.x() < other.pos.x() + other.size.x() &&
				 pos.x() + size.x() > other.pos.x() ) && 
				( pos.y() < other.pos.y() + other.size.y() && 
			          pos.y() + size.y() > other.pos.y());
		}
		virtual bool DeathAnimation( float dt ) {
		}
		void kill() { dead = true; }
		void revive() { dead = false; }
	protected:
		bool dead=0;
		Vec2 pos;
		Vec2 velocity;
		Vec2 size;
		Vec4 color;
};
#endif
