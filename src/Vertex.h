#ifndef VERTEX_STRUCT_H
#define VERTEX_STRUCT_H
#include "vector_typedef.h"
#include "vec4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"

// a vertex data struct.
/*
 * A vertex is not neccessarily a position in space though in most representations
 * is a position space.
 *
 * A vertex in 3D graphics and just graphics in general. Are just pieces of data
 * that the GPU reads and essentially parses to be used in the rendering process.
 *
 * In my case a vertex contains a position, a uv coordinate and a color.
 */
// A class is absolutely unneccessary for this so I used a struct ( it makes more sense with a struct regardless, even if C++ structs are pretty much classes. )
struct Vertex{
	Vertex(Vec3 pos, Vec2 uv, Vec4 color) : pos(pos), uv(uv), color(color){}
	Vec3 pos;
	Vec2 uv;
	Vec4 color;
};

#endif
