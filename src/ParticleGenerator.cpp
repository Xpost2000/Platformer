#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vec2 origin, Vec2 velocity, Vec2 acceleration) : origin(origin), velocity(velocity), acceleration(acceleration){
	RandomFloat fl(-200, 200);
	for(int i = 0; i < 1000; i++){
		particles.push_back(Particle(origin+Vec2(fl()), velocity, acceleration+Vec2(fl()), Vec2(10)+Vec2(fl()), Vec4(1.0), 0, 300));
	}
}

void ParticleGenerator::respawnParticle(Particle& par){
	RandomFloat fl(-200, 200);
	par = Particle(origin+Vec2(fl()), velocity, acceleration +Vec2(fl()), Vec2(30), Vec4(1.0, 0.0, 0.0, 1.0), 0, 150);
}

void ParticleGenerator::update(float dt){
	RandomInt dir(-1, 1);
	for(auto& p : particles){
		if(p.lifetime > 0){
			p.velocity.x() = p.velocity.x() + p.acceleration.x();
			p.pos.x() += (p.velocity.x() * dir())* dt;
			p.pos.y() += p.velocity.y() * dt;
			p.size.x() -= 25 * dt;
			p.size.y() -= 25 * dt;
			p.color.r() -= dt;
			p.color.g() -= dt;
			p.color.a() -= dt;
			p.lifetime -= dt;
		}else{
			respawnParticle(p);
		}
	}
}
