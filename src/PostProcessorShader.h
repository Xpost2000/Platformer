#ifndef POST_PROCESSOR_SHADER_H
#define POST_PROCESSOR_SHADER_H
#include "IDevice.h"
#include "IShaderSet.h"
#include "matrix_typedef.h"

class ShaderUniform;
class PostProcessorShader : public IShaderSet{
	public:
	PostProcessorShader(const std::shared_ptr<IDevice>& dev);
	~PostProcessorShader();
	void setTex(int);
	void setDt(float);
	void setFade(bool);
	private:
	std::shared_ptr<IDevice> device = nullptr;
	ShaderUniform* tex = nullptr;	
	ShaderUniform* shouldFade = nullptr;
	ShaderUniform* dt = nullptr;
};

#endif
