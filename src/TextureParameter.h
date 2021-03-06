#ifndef TEX_PARAM_H
#define TEX_PARAM_H
#include <GL/glew.h>

/*
 * Contains strongly typed enums
 * for usage in IDevice texture related classes.
 */

enum class TextureTarget : int {
	TEXTURE1D = GL_TEXTURE_1D,
	TEXTURE2D = GL_TEXTURE_2D,
	TEXTURE3D = GL_TEXTURE_3D
};

enum class TextureParameter: int{
	WRAP_T = GL_TEXTURE_WRAP_T,
	WRAP_S = GL_TEXTURE_WRAP_S,
	MAG_FILTER = GL_TEXTURE_MAG_FILTER,
	MIN_FILTER = GL_TEXTURE_MIN_FILTER
};

enum class ParamValue: int{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT
};

#endif
