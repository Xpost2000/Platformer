#ifndef LIGHT_STRUCT_H
#define LIGHT_STRUCT_H
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec3.hpp"
struct Light{
	Light() : Light(1, Vec3(1), Vec2(0)){}
	Light(const Light& other) = default;
	Light(float strength, Vec3 color, Vec2 pos) : strength(strength), color(color), pos(pos) {}
	float strength;
	Vec3 color;
	Vec2 pos;
};
#endif
