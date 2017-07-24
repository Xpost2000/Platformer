#ifndef PARTICLE_GEN_H
#define PARTICLE_GEN_H
#include <vector>
#include "ParticleStruct.h"
#include "RandomNumberGenerator.h"
/*
 * Let's just generically create a particle generator.
 * I'm going to have slight problems making a good generator...
 *
 * But the plan is not to make a good generator.
 * It's just to make a generator that is good enough for a game.
 * We'll leave that to tech demos in which I spend meticulous hours
 * tweaking settings.
 *
 * This particle generator is extremely simple and just enough to create fire-ish looking effects.
 * Not very flexible for anything else.
 */
class ParticleGenerator{
	public:
		ParticleGenerator(Vec2 origin, Vec2 velocity = Vec2(150,150), Vec2 acceleration=Vec2(15, 15), Vec2 size=Vec2(30), Vec4 color = Vec4(1), int lifetime = 150, Vec2 posOffsetMinMax = Vec2(-15, 15), Vec2 sizeOffsetMinMax = Vec2(-10, 10), Vec2 speedVariance = Vec2(-15, 15), int maxParticles = 5000);
		~ParticleGenerator(){}
		std::vector<Particle>& get_particles() { return particles; }
		void setActive(bool a) { active = a; }
		void setBothDirections(bool a) { bothDir = a; }
		void setOrigin(Vec2 pos) { origin = pos; }
		void update(float dt);
		void sort();
	private:
		bool active=true;
		bool bothDir=true;
		void respawnParticle(Particle&);
		Vec2 origin;
		Vec2 velocity;
		Vec2 acceleration;
		Vec2 size;
		Vec4 color;
		Vec2 posOffsetMinMax;
		Vec2 sizeOffsetMinMax;
		Vec2 speedVariance;
		int lifetime;
		std::vector<Particle> particles;
};
#endif
