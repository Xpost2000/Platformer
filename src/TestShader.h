#ifndef TEST_SHADER_SET_H
#define TEST_SHADER_SET_H
#include "IDevice.h"
#include "IShaderSet.h"
#include "matrix_typedef.h"
class ShaderUniform;
/*
 * This is the test shader I used for 
 * "Mountainy Mountains".
 *
 * I used this to test the IShaderSet interface
 * to (technically) reduce the amount of code written
 * in the main function.
 */
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
