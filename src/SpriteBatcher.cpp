#include "SpriteBatcher.h"

SpriteBatcher::SpriteBatcher(const std::shared_ptr<IDevice>& dev) : device(dev){
	vbo = new Buffer(device);
	vao = new VertexArray(device);
	vertices.clear();
}

SpriteBatcher::~SpriteBatcher(){
	delete vbo;
	delete vao;
}

void SpriteBatcher::draw(Vec2 pos, Vec4 uvs, Vec2 size, Vec4 color){
	/*
	 * 	v.push_back(Vertex(r.x, r.y));
		v.push_back(Vertex(r.x, r.y+r.y1));
		v.push_back(Vertex(r.x+r.x1, r.y));
		v.push_back(Vertex(r.x+r.x1, r.y));
		v.push_back(Vertex(r.x, r.y+r.y1));
		v.push_back(Vertex(r.x+r.x1, r.y+r.y1));

		I'm hoping I setup the UVs correctly...
	 */
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y(), 1.0), Vec2(uvs.x(), uvs.w()), color));
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y() + size.y(), 1.0), Vec2(uvs.x(), uvs.y()), color));
	vertices.push_back(Vertex(Vec3(pos.x()+size.x(), pos.y(), 1.0), Vec2(uvs.z(), uvs.w()), color));
	vertices.push_back(Vertex(Vec3(pos.x()+size.x(), pos.y(), 1.0), Vec2(uvs.z(), uvs.w()), color));
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y() + size.y(), 1.0), Vec2(uvs.x(), uvs.y()), color));
	vertices.push_back(Vertex(Vec3(pos.x() + size.x(), pos.y() + size.y(), 1.0), Vec2(uvs.z(), uvs.y()), color));
}

void SpriteBatcher::draw(Vec2 pos, Vec4 uvs, Vec2 size, Vec4 tl, Vec4 tr, Vec4 bl, Vec4 br){
	/*
	 * 	v.push_back(Vertex(r.x, r.y));
		v.push_back(Vertex(r.x, r.y+r.y1));
		v.push_back(Vertex(r.x+r.x1, r.y));
		v.push_back(Vertex(r.x+r.x1, r.y));
		v.push_back(Vertex(r.x, r.y+r.y1));
		v.push_back(Vertex(r.x+r.x1, r.y+r.y1));

		I'm hoping I setup the UVs correctly...
	 */
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y(), 1.0), Vec2(uvs.x(), uvs.w()), tl));
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y() + size.y(), 1.0), Vec2(uvs.x(), uvs.y()), bl));
	vertices.push_back(Vertex(Vec3(pos.x()+size.x(), pos.y(), 1.0), Vec2(uvs.z(), uvs.w()), tr));
	vertices.push_back(Vertex(Vec3(pos.x()+size.x(), pos.y(), 1.0), Vec2(uvs.z(), uvs.w()), tr));
	vertices.push_back(Vertex(Vec3(pos.x(), pos.y() + size.y(), 1.0), Vec2(uvs.x(), uvs.y()), bl));
	vertices.push_back(Vertex(Vec3(pos.x() + size.x(), pos.y() + size.y(), 1.0), Vec2(uvs.z(), uvs.y()), br));
}

void SpriteBatcher::render(bool wireframe){
	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();
	vbo->bufferData(BufferTypes::ARRAY_BUFFER, vertices.size() * sizeof(Vertex), NULL, BufferUsage::DYNAMIC_DRAW);
	device->bufferSubData(BufferTypes::ARRAY_BUFFER, 0, vertices.size()*sizeof(Vertex), vertices.data());
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)offsetof(Vertex, pos));
	vao->attribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
	vao->attribPointer(2, 4, GL_FLOAT, false, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	vao->enableAttribute(0);
	vao->enableAttribute(1);
	vao->enableAttribute(2);
	// Oh god... First un hidden api call....
	GLenum draw_mode = wireframe ? GL_LINES : GL_TRIANGLES;
	glDrawArrays(draw_mode, 0, vertices.size());
	vertices.clear();
}
