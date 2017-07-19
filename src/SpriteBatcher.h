#ifndef SPRITE_BATCHER_H
#define SPRITE_BATCHER_H
#include <vector>
#include "Vertex.h"
#include "IDevice.h"
#include "DrawModes.h"
#include "VertexArray.h"
#include "Buffer.h"

struct Vec4{
	Vec4( float x, float y, float w, float h ):
		x(x), y(y), w(w), h(h){}
	float x, y, w, h;
	// I had to cheat this...
	// TODO : Make a proper vec4 class so I don't cheat this.
};

/*
 * A simple sprite batcher that does all it needs to fit my needs.
 */
class SpriteBatcher{
	public:
		SpriteBatcher(const std::shared_ptr<IDevice>& dev);
		~SpriteBatcher();
		void draw(Vec2 pos, Vec4 uvs, Vec2 size, Vec3 color);
		void render();
	private:
		std::vector<Vertex> vertices;
		std::shared_ptr<IDevice> device = nullptr;
		Buffer* vbo = nullptr;
		VertexArray* vao = nullptr;
};

#endif
