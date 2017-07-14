#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <memory>
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GLDevice.h"
#include "Bitmap.h"
#include "ShaderUniform.h"
#include "Texture.h"
namespace core{
	using Buffer = std::shared_ptr<Buffer>;
	using VertexArray = std::shared_ptr<VertexArray>;
	using IDevice = std::shared_ptr<GLDevice>;
	using Shader = std::shared_ptr<Shader>;
	using ShaderProgram = std::shared_ptr<ShaderProgram>;
	using ShaderUniform = std::shared_ptr<ShaderUniform>;
	using Texture = std::shared_ptr<Texture>;
	using Bitmap = std::shared_ptr<Bitmap>;
	};
#endif
