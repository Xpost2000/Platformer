#ifndef UTIL_H
#define UTIL_H

#include "../vec2.hpp"
#include "../vector_typedef.h"

#include <cmath>
Vec2 SnapToGrid( Vec2 original, Vec2 grid_dims ){
	Vec2 new_vec;
	new_vec.x() = floor(original.x() / grid_dims.x()) * grid_dims.x();
        new_vec.y() = floor(original.y() / grid_dims.y()) * grid_dims.y();	
	return new_vec;
}

#endif
