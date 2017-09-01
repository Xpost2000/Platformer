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

#define BLOCK 1
#define PLAYER 2
#define PROGRESSOR 33
#define STBLOCK 3
#define BGRNDBLOCK 4

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
		// I just realized I was an idiot.
		// Was kind of stuck with the editor in trying to test if the current object pointer
		// would move if I editted it ( although I know it should ). It was then I realized
		// I never returned by reference.... But by value!
		// Stupid I know.
		//
		// EDIT: It returns by reference now since I just edited it as I typed this
		Vec2& getPos(){ return pos; }
		Vec2& getVelocity(){ return velocity; }
		// for animations and stuff like that
		// I plan to have the objects calculate their own uvs.
		virtual Vec4 getUvs()  { return uvs; }
		Vec2& getSize(){ return size; }
		Vec4& getColor(){ return color; }
		void setPos(Vec2 pos) { this->pos = pos; }
		void setVelocity(Vec2 velocity) { this->velocity = velocity; }
		// this is virtual because they may implement
		// state changing on this.
		bool& isDead() { return dead; }
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
		bool intersect_point( Vec2 pointPos ){
			aabb pBB(pointPos, Vec2(1));
			return bb.intersect(pBB);
		}
		bool interesect_point_pos( Vec2 pointPos ){
			Entity ptr( pointPos, Vec2(1), Vec2(0), Vec4(0) );
			return intersect(ptr);
		}
		void set_aabb(Vec2 pos, Vec2 size){ bb = aabb(pos, size); }
		// each entity might reposition the aabb in their own way.
		virtual void reposition_aabb() { bb = aabb( pos , bb.size); }
		virtual bool DeathAnimation( float dt ) {
		}
		virtual void kill() {}
		virtual void revive() {}
		aabb& get_aabb() { return bb; }
		// I use a pointer to a generic entity in the
		// editor. For the copy and pasting I do not store the entities
		// directly but I use the entity manager to do things. The entity manager
		// adds using functions like create_block , create_enemy.
		// Each type has a different magic_number.
		int magic=0;
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
