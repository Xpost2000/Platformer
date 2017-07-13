#include "ShaderProgram.h"
#include "IDevice.h"

ShaderProgram::ShaderProgram(const std::shared_ptr<IDevice>& device){
	obj = glCreateProgram();
	this->device = device;
}

ShaderProgram::ShaderProgram(){
	obj = glCreateProgram();
}

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(obj);
}
