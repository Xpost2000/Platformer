#ifndef TEST_SHADER_SET_H
#define TEST_SHADER_SET_H
#include "IDevice.h"
#include "IShaderSet.h"
#include "matrix_typedef.h"
class ShaderUniform;
class TestShader : public IShaderSet{
	public:
	TestShader(const std::shared_ptr<IDevice> &dev);
	~TestShader();
	void setD(float);
	void setTex(int);
	void setMatrix(Matrix4f);
	private:
	ShaderUniform *d = nullptr;
	ShaderUniform *tex = nullptr;
	ShaderUniform *matrix = nullptr;
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
