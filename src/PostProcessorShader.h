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
	private:
	std::shared_ptr<IDevice> device = nullptr;
	ShaderUniform* tex = nullptr;	
};

#endif
