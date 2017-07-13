#include "Shader.h"

Shader::Shader( const std::shared_ptr<IDevice>& dev, ShaderType type) : device(dev), compiled(false){
	obj = glCreateShader(static_cast<int>(type));
}

Shader::Shader( ShaderType type ) : compiled(false){
	obj = glCreateShader(static_cast<int>(type));
}

Shader::~Shader(){
	glDeleteShader(obj);
}
