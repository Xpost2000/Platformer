#include "Shader.h"
#include "IDevice.h"
#include <iostream>

// I only used the not keyword for readability and also cause it's a gimmick :)
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
	if(not compiled){
	try{
		if(std::is_null_pointer< decltype(device) >::value){
			throw std::runtime_error("Device is nullptr");
		}
		device->compileShader(*this);
		compiled = true;
	}
	catch(std::exception const & e){
		std::cout << "Shader Exception :: " << e.what() << std::endl;
	}
	}
}

void Shader::source(GLsizei sz, std::string str, const GLint* len){
	if(not compiled){
	try{
		if(std::is_null_pointer< decltype(device) >::value){
			throw std::runtime_error("Device is nullptr");
		}
		device->shaderSource(*this, sz, str, len);
	}
	catch(std::exception const & e){
		std::cout << "Shader Exception :: " << e.what() << std::endl;
	}
	}
}

std::string Shader::get_log(){
	std::string res = std::string("Compilation status is perfect.");
	if(compiled){
		try{
			if(std::is_null_pointer< decltype(device) >::value){
				throw std::runtime_error("Device is nullptr");
			}
			GLint log_size = 0;
			log_size = device->getShaderInteger(*this, ShaderInfo::INFO_LOG_SIZE);
			GLchar log [log_size];
			glGetShaderInfoLog(obj, log_size, &log_size, &log[0]);
			res = std::string(log);
			if(log_size == 0){ res = std::string( "Compilation status is perfect" );} 
		}
		catch(std::exception const & e){
			std::cout << "Shader Exception :: " << e.what() << std::endl;
			return std::string(e.what());
		}
	}
	return res;
}
