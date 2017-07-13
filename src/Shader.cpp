#include "Shader.h"
#include "IDevice.h"
#include <iostream>

Shader::Shader( const std::shared_ptr<IDevice>& dev, ShaderType type) : device(dev), compiled(false){
	obj = glCreateShader(static_cast<int>(type));
}

Shader::Shader( ShaderType type ) : compiled(false){
	obj = glCreateShader(static_cast<int>(type));
}

Shader::~Shader(){
	glDeleteShader(obj);
}

void Shader::compile(){
	try{
		if(device==nullptr){
			throw std::runtime_error("Device is nullptr");
		}
		device->compileShader(*this);
	}
	catch(std::exception const & e){
		std::cout << "Shader Exception :: " << e.what() << std::endl;
	}
}

void Shader::source(GLsizei sz, std::string str, const GLint* len){
	try{
		if(device==nullptr){
			throw std::runtime_error("Device is nullptr");
		}
		device->shaderSource(*this, sz, str, len);
	}
	catch(std::exception const & e){
		std::cout << "Shader Exception :: " << e.what() << std::endl;
	}
}
