#include "ParticleGenerator.h"
#include <algorithm>
/*

ParticleGenerator::ParticleGenerator(Vec2 origin, Vec2 velocity, Vec2 acceleration) : origin(origin), velocity(velocity), acceleration(acceleration){
	RandomFloat fl(-200, 200);
	RandomFloat ft(-30, 30);
	for(int i = 0; i < 1000; i++){
		particles.push_back(Particle(origin+Vec2(ft(), ft()), velocity, acceleration+Vec2(fl()), Vec2(10)+Vec2(fl()), Vec4(1.0), 0, 300));
	}
}

void ParticleGenerator::respawnParticle(Particle& par){
	RandomFloat fl(-200, 200);
	RandomFloat fa(150, 200);
	par = Particle(origin+Vec2(fl()), velocity, acceleration +Vec2(fl()), Vec2(30), Vec4(1.0, 0.0, 0.0, 1.0), 0, fa());
}

void ParticleGenerator::update(float dt){
	RandomInt dir(-1, 1);
	for(auto& p : particles){
		if(p.lifetime > 0){
			p.velocity.x() = p.velocity.x() + p.acceleration.x();
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
*/
// Above was me testing things. Now the more serious version.
ParticleGenerator::ParticleGenerator(Vec2 origin, Vec2 velocity, Vec2 acceleration, Vec2 size, Vec4 color, int lifetime, Vec2 posOffsetMinMax, Vec2 sizeOffsetMinMax, Vec2 speedVariance , int maxParticles):
origin(origin), velocity(velocity), acceleration(acceleration), size(size), color(color), posOffsetMinMax(posOffsetMinMax), sizeOffsetMinMax(sizeOffsetMinMax), speedVariance(speedVariance), lifetime(lifetime){
	RandomFloat pOffset(posOffsetMinMax.x(), posOffsetMinMax.y());
	RandomFloat sOffset(sizeOffsetMinMax.x(), sizeOffsetMinMax.y());
	RandomFloat spOffset(speedVariance.x(), speedVariance.y());
	RandomFloat lf(-10, 10);
	for( int i = 0; i < maxParticles; ++i ){
		particles.push_back(Particle(origin+Vec2(pOffset(), pOffset()), velocity+Vec2(spOffset(), spOffset()), acceleration, size+Vec2(sOffset(), sOffset()), color, 0, lifetime + lf()));
	}
}

void ParticleGenerator::update(float dt){
	if(active){
		if(bothDir){
			RandomInt dir(-1, 1);
			for(auto& p : particles){
				if(p.lifetime > 0){
					p.velocity.x() = p.velocity.x() + p.acceleration.x();
					p.velocity.y() = p.velocity.y() + p.acceleration.y();
					p.pos.x() += (p.velocity.x() * dir())* dt;
					p.pos.y() += p.velocity.y() * dt;
					p.size.x() -= 10 * dt;
					p.size.y() -= 10 * dt;
					p.color.r() += dt;
					p.color.g() += dt;
					p.color.b() += dt;
					p.color.a() -= dt;
					p.lifetime -= dt;
				}else{
					respawnParticle(p);
				}
			}
		}
		else{
			for(auto& p : particles){
				if(p.lifetime > 0){
					p.velocity.x() = p.velocity.x() + p.acceleration.x();
					p.velocity.y() = p.velocity.y() + p.acceleration.y();
					p.pos.x() += p.velocity.x() * dt;
					p.pos.y() += p.velocity.y() * dt;
					p.size.x() -= 10 * dt;
					p.size.y() -= 10 * dt;
					p.color.r() += dt;
					p.color.g() += dt;
					p.color.b() += dt;
					p.color.a() -= dt;
					p.lifetime -= dt;
				}else{
					respawnParticle(p);
				}
			}
		}	
		sort();
	}
}

void ParticleGenerator::respawnParticle(Particle& par){
	RandomFloat pOffset(posOffsetMinMax.x(), posOffsetMinMax.y());
	RandomFloat sOffset(sizeOffsetMinMax.x(), sizeOffsetMinMax.y());
	RandomFloat spOffset(speedVariance.x(), speedVariance.y());
	RandomFloat lf(-10, 10);
	par = Particle(origin+Vec2(pOffset(), pOffset()), velocity+Vec2(spOffset(), spOffset()), acceleration, size+Vec2(sOffset(), sOffset()), color, 0, lifetime+lf());
}

void ParticleGenerator::sort(){
	std::sort( particles.begin(), particles.end() );
}
