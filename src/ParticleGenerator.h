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
 */
class ParticleGenerator{
	public:
		ParticleGenerator(Vec2 origin, Vec2 velocity, Vec2 acceleration);
		~ParticleGenerator(){}
		std::vector<Particle>& get_particles() { return particles; }
		void update(float dt);
	private:
		void respawnParticle(Particle&);
		Vec2 origin;
		Vec2 velocity;
		Vec2 acceleration;
		std::vector<Particle> particles;
};
#endif
