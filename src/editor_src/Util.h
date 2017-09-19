#ifndef UTIL_H
#define UTIL_H

#include "../vec2.hpp"
#include "../vector_typedef.h"

#include <cmath>
Vec2 SnapToGrid( Vec2 original, Vec2 grid_dims ){
	Vec2 new_vec;
	/*
		This is the classical example that people use when they
		want to show people how to do grid snapping or tile placement or something along those lines.
		Common math indicates that dividing and multiplying by the samething cancels the operation out.
		In most untyped languages yes. In typed languages we get to specify our own types ( unless we use auto here ).
		I use floor to round the division(down) and then multiply which gives the correct result.
	*/
	new_vec.x() = floor(original.x() / grid_dims.x()) * grid_dims.x();
        new_vec.y() = floor(original.y() / grid_dims.y()) * grid_dims.y();	
	return new_vec;
}

#endif
