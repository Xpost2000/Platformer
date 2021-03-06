#ifndef LIGHTING_SHADER_H
#define LIGHTING_SHADER_H
#include "IShaderSet.h"
#include "IDevice.h"
#include "ShaderUniform.h"
#include "vec2.hpp"
#include "vector_typedef.h"
#include "matrix_typedef.h"
#include "LightStruct.h"
#include <glm/glm.hpp>
/*
 * This is the equivalent of the default shader but the core difference
 * being that it supports 2D lighting.
 */
class LightShader : public IShaderSet{
	public:
		LightShader(const std::shared_ptr<IDevice>& dev);
		~LightShader();
		void setTex(int);
		void setTextured(bool);
		void setView(glm::mat4);
		void setProj(glm::mat4);
		void setLight(int index, Light l);
	private:
		std::shared_ptr<IDevice> device = nullptr;
		ShaderUniform* textured = nullptr;
		ShaderUniform* tex = nullptr;
		ShaderUniform* projMat = nullptr;
		ShaderUniform* viewMat = nullptr;
		ShaderUniform lightPos [10];
		ShaderUniform lightColor [10];
		ShaderUniform lightPower [10];
};
#endif
