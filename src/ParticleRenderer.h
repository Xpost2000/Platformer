#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H
#include "vector_typedef.h"
#include "vec4.hpp"
#include "IDevice.h"

/*
 * contains a sprite batcher to render
 * particle generators :)
 */
class SpriteBatcher;
class ParticleGenerator;
class Texture;
class ParticleRenderer{
	public:
	ParticleRenderer(const std::shared_ptr<IDevice>& dev);
	~ParticleRenderer();
	// render with additive blending enabled.
	void render( ParticleGenerator& );
	void render( ParticleGenerator&, Texture&, Vec4 );
	private:
	std::shared_ptr<IDevice> device = nullptr;
	SpriteBatcher* batch = nullptr;
};

#endif
