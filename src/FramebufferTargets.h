#ifndef FRAMEBUFFER_TARGETS_H
#define FRAMEBUFFER_TARGETS_H
#include <GL/glew.h>

enum class FrameBufferTarget : int {
	DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
	READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
	FRAMEBUFFER = GL_FRAMEBUFFER
};

#endif
