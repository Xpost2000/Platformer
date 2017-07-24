/*
 * Structure to be used
 * when I implement a particle system.
 */
#ifndef PARTICLE_STRUCT_H
#define PARTICLE_STRUCT_H

#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec4.hpp"
struct Particle{
	Particle(Vec2 pos, Vec2 velocity, Vec2 size, Vec4 color, float angle, int lifetime):pos(pos), velocity(velocity), size(size), color(color), angle(angle), lifetime(lifetime) {}
	Particle() : Particle(Vec2(0.0), Vec2(0.0), Vec2(0.0), Vec4(1.0), 0.0, 0.0){}
	~Particle(){}
	bool isAlive() { return (lifetime < 0); }
	// TODO: ADD UPDATE FUNCTION
	// Or just make emitters that handle the properties for me??
	// I'll just make different generators that handle based on the type.
	Vec2 pos;
	Vec2 velocity;
	Vec2 size;
	Vec4 color;
	float angle;
	int lifetime;
};

#endif
