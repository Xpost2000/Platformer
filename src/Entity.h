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

struct aabb{
	aabb(){}
	aabb(Vec2 pos, Vec2 size) : pos(pos), size(size){}
	aabb(const aabb& other) = default;
	Vec2 pos, size;
	bool intersect(aabb& other){
			return ( pos.x() < other.pos.x() + other.size.x() &&
				 pos.x() + size.x() > other.pos.x() ) && 
				( pos.y() < other.pos.y() + other.size.y() && 
			          pos.y() + size.y() > other.pos.y());
	}
};

class Block;
class Entity{
	public:
		Entity(){}
		Entity(const Entity& other) = default;
		Entity(Vec2 pos, Vec2 size, Vec2 velocity, Vec4 color)
		: pos(pos), size(size), velocity(velocity), color(color){
			// by default the aabb matches the pos and size of the entity.
			bb = aabb(pos, size);
		}
		virtual void update(float dt, std::vector<Block>& blocks){}
		Vec2 getPos(){ return pos; }
		Vec2 getVelocity(){ return velocity; }
		// for animations and stuff like that
		// I plan to have the objects calculate their own uvs.
		Vec4 getUvs()  { return uvs; }
		Vec2 getSize(){ return size; }
		Vec4 getColor(){ return color; }
		// this is virtual because they may implement
		// state changing on this.
		bool isDead() { return dead; }
		// this is collision between the size of the object.
		bool intersect( Entity &other )	{
			return ( pos.x() < other.pos.x() + other.size.x() &&
				 pos.x() + size.x() > other.pos.x() ) && 
				( pos.y() < other.pos.y() + other.size.y() && 
			          pos.y() + size.y() > other.pos.y());
		}
		bool intersect_aabb( Entity &other )	{
			return bb.intersect(other.bb);
		}
		void set_aabb(Vec2 pos, Vec2 size){ bb = aabb(pos, size); }
		// each entity might reposition the aabb in their own way.
		virtual void reposition_aabb() { bb = aabb( pos , bb.size); }
		virtual bool DeathAnimation( float dt ) {
		}
		virtual void kill() = 0;
		virtual void revive() = 0;
		aabb& get_aabb() { return bb; }
	protected:
		aabb bb;
		bool dead=0;
		Vec4 uvs;
		Vec2 pos;
		Vec2 velocity;
		Vec2 size;
		Vec4 color;
};
#endif
