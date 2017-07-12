#ifndef OBJECT_TYPES_HPP
#define OBJECT_TYPES_HPP

/*
 * This header file contains an enum class to identify what type the object is.
 */

// Contains the basic types that I can list
enum class HandleType: int{
	HANDLE_SHADER,
	HANDLE_SHADERPROGRAM,
	HANDLE_BUFFER,
	HANDLE_VERTEXARRAY,
	HANDLE_TEXTURE,
	HANDLE_FRAMEBUFFER,
	HANDLE_RENDERBUFFER
};

#endif
