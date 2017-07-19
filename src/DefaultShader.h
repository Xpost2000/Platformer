#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H
#include "IDevice.h"
#include <glm/glm.hpp>
#include "IShaderSet.h"
#include "matrix_typedef.h"
/*
 * This class is a preset shader that contains the default
 * shader that I will use to draw sprites and other things.
 */
class ShaderUniform;
class DefaultShader : public IShaderSet{
	public:
	DefaultShader(const std::shared_ptr<IDevice>& dev);
	~DefaultShader();
	void setTex(int);
	void setTextured(bool);
	// proj, view
	void setMatrices( Matrix4f, Matrix4f );
	void setMatrices( glm::mat4, glm::mat4 );
	private:
	ShaderUniform *textured = nullptr;
	ShaderUniform *tex = nullptr;
	ShaderUniform *projMat = nullptr;
	ShaderUniform *viewMat = nullptr;
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
