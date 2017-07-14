#ifndef FEATURE_HPP
#define FEATURE_HPP
/*
 * Header file that contains feature flags for OpenGL .
 used with IDevice::Enable and IDevice::Disable
 */
#include <GL/glew.h>
	enum class Feature: int{
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_3D = GL_TEXTURE_3D,
		TEXTURE_1D = GL_TEXTURE_1D,
		ALPHA_TEST = GL_ALPHA_TEST,
		BLEND = GL_BLEND,
		DEPTH_TEST = GL_DEPTH_TEST,
		STENCIL_TEST = GL_STENCIL_TEST
	};
#endif
