#ifndef BUFFER_USAGE_H
#define BUFFER_USAGE_H

/*
 * Unlike the enum class types.
 * This should be easy to work with since I'm only doing draw types.
 * So no need to do assignment to OGL enums.
 */

enum class BufferUsage : int{
	STATIC_DRAW = GL_STATIC_DRAW,
	STATIC_READ = GL_STATIC_READ,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	STREAM_DRAW = GL_STREAM_DRAW,
	STREAM_READ = GL_STREAM_READ,
};

#endif
