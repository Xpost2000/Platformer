#include "ParticleRenderer.h"
#include "Texture.h"
#include "SpriteBatcher.h"
#include "ParticleGenerator.h"

ParticleRenderer::ParticleRenderer(const std::shared_ptr<IDevice>& dev) : device(dev){
	batch = new SpriteBatcher(device);
}

ParticleRenderer::~ParticleRenderer(){
	delete batch;
}

void ParticleRenderer::render( ParticleGenerator& pg ){
	// manually enable additive blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	pg.sort();
	for(auto & p : pg.get_particles()){
		if(p.lifetime > 0)
		batch->draw(p.pos, Vec4(0), p.size, p.color);
	}
	batch->render();

	device->enableAlpha(); // re-enable alpha blending
}
void ParticleRenderer::render( ParticleGenerator& pg, Texture& tex, Vec4 uv ){
	// enable additive blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	tex.bindTexture(TextureTarget::TEXTURE2D);
	pg.sort();
	for(auto & p : pg.get_particles()){
		if(p.lifetime > 0)
		batch->draw(p.pos, uv, p.size, p.color);
	}
	batch->render();
	tex.unbindTexture(TextureTarget::TEXTURE2D);

	device->enableAlpha(); // re-enable alpha blending
}
