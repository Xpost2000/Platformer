#ifndef SHADER_INFO_H
#define SHADER_INFO_H
#include <GL/glew.h>

/*
 * Strongly typed enums for Shader related functions
 */

enum class ShaderInfo : int{
	COMPILE_STATUS = GL_COMPILE_STATUS,
	INFO_LOG_SIZE = GL_INFO_LOG_LENGTH,
	DELETE_FLAG = GL_DELETE_STATUS,
	SOURCE_SIZE = GL_SHADER_SOURCE_LENGTH
};

enum class ShaderType : int{
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER
};

#endif
