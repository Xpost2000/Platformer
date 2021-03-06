#ifndef BUFFER_TYPES_HPP
#define BUFFER_TYPES_HPP
#include <GL/glew.h>
/*
 * Enum class that specifies possible buffer targets.
 */

enum class BufferTypes : int{
	ARRAY_BUFFER = GL_ARRAY_BUFFER,
	ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	ATOMIC_CTR_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
	COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
	COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
	DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
	DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
	PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
	QUERY_BUFFER = GL_QUERY_BUFFER,
	SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
	TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER
};
#endif
