#ifndef SPRITE_BATCHER_H
#define SPRITE_BATCHER_H
#include <vector>
#include "Vertex.h"
#include "IDevice.h"
#include "DrawModes.h"
#include "VertexArray.h"
#include "Buffer.h"

/*
 * A simple sprite batcher that does all it needs to fit my needs.
 * Which includes. Batching all vertices into a single VBO.
 *
 * TODO : Add index / element based rendering to increase performance
 * 	  especially on more intense scenes.
 */
class SpriteBatcher{
	public:
		SpriteBatcher(const std::shared_ptr<IDevice>& dev);
		~SpriteBatcher();
		void draw(Vec2 pos, Vec4 uvs, Vec2 size, Vec4 color);
		// manually set a color for each corner.
		void draw(Vec2 pos, Vec4 uvs, Vec2 size, Vec4 tl, Vec4 tr, Vec4 bl, Vec4 br);
		void render(bool wireframe=false);
	private:
		std::vector<Vertex> vertices;
		std::shared_ptr<IDevice> device = nullptr;
		Buffer* vbo = nullptr;
		VertexArray* vao = nullptr;
};

#endif
