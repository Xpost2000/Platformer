#ifndef LIGHTING_SHADER_H
#define LIGHTING_SHADER_H
#include "IShaderSet.h"
#include "IDevice.h"
#include "ShaderUniform.h"
#include "vec2.hpp"
#include "vector_typedef.h"
#include "matrix_typedef.h"
#include <glm/glm.hpp>
class LightShader : public IShaderSet{
	public:
		LightShader(const std::shared_ptr<IDevice>& dev);
		~LightShader();
		void setTex(int);
		void setTextured(bool);
		void setView(glm::mat4);
		void setProj(glm::mat4);
		void setLightPos(int index, Vec2 val){
			lightPos[index].uniformf(val.x(), val.y());
		}
	private:
		std::shared_ptr<IDevice> device = nullptr;
		ShaderUniform* textured = nullptr;
		ShaderUniform* tex = nullptr;
		ShaderUniform* projMat = nullptr;
		ShaderUniform* viewMat = nullptr;
		ShaderUniform lightPos [10];
};
#endif
