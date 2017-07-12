#ifndef DRAW_MODES_H
#define DRAW_MODES_H
#include <GL/glew.h>

enum class DrawMode: int{
	TRIANGLES = GL_TRIANGLES,
	TRIANGLE_STRIPS = GL_TRIANGLE_STRIP,
	POINTS = GL_POINTS,
	LINES = GL_LINES,
	LINE_STRIPS = GL_LINE_STRIP
};

#endif
