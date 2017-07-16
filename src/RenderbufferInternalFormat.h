#ifndef RENDER_BUFFER_INTERNAL_H
#define RENDER_BUFFER_INTERNAL_H
#include <GL/glew.h>
/*
 * I'll add more and change the DEFAULT name as I continue
 * finding out more GLenums that can be used for the internal
 * format argument of the glRenderbufferStorage function
 */
enum class RenderBufferInternalFormat: int{
	DEFAULT = GL_DEPTH24_STENCIL8
};
#endif
