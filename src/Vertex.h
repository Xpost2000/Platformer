#ifndef VERTEX_STRUCT_H
#define VERTEX_STRUCT_H
#include "vector_typedef.h"
#include "vec3.hpp"
#include "vec2.hpp"

// a vertex data struct.
struct Vertex{
	Vertex(Vec3 pos, Vec2 uv, Vec3 color) : pos(pos), uv(uv), color(color){}
	Vec3 pos;
	Vec2 uv;
	Vec3 color;
};

#endif
