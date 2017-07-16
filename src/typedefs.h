#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <memory>
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GLDevice.h"
#include "Framebuffer.h"
#include "Renderbuffer.h"
#include "Bitmap.h"
#include "ShaderUniform.h"
#include "Texture.h"
#include "sdl_surface_load_image_wrapper.h"
#include "vector_typedef.h"
#include "matrix_typedef.h"
// Please don't do using namespace on this... Otherwise name conflicts and errors everywhere.
namespace ptrs{
	using Buffer = std::shared_ptr<Buffer>;
	using VertexArray = std::shared_ptr<VertexArray>;
	using IDevice = std::shared_ptr<GLDevice>;
	using Shader = std::shared_ptr<Shader>;
	using ShaderProgram = std::shared_ptr<ShaderProgram>;
	using ShaderUniform = std::shared_ptr<ShaderUniform>;
	using Texture = std::shared_ptr<Texture>;
	using Bitmap = std::shared_ptr<Bitmap>;
	using ImageSurface = std::shared_ptr<ImageSurface>;
	using Renderbuffer = std::shared_ptr<Renderbuffer>;
	using Framebuffer = std::shared_ptr<Framebuffer>;
	};
#endif
