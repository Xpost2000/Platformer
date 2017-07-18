#include "ShaderProgram.h"
#include <iostream>
#include "Shader.h"
#include "IDevice.h"

ShaderProgram::ShaderProgram(const std::shared_ptr<IDevice>& device, Shader& a, Shader& b){
	obj = glCreateProgram();
	this->device = device;
	attach(a);
	attach(b);
}

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

void ShaderProgram::use(){
	try{
		if(device == nullptr)
			throw std::runtime_error("Device is nullptr");
		if(!used){
		device->useProgram(*this);
		used = true;
		}
	}catch(std::exception const & e){
		std::cout << "ShaderProgram Exception :: " << e.what() << std::endl;
	}
}

void ShaderProgram::unuse(){
	try{
		if(device == nullptr)
			throw std::runtime_error("Device is nullptr");
		if(used){
		device->unuseProgram();
		used = false;
		}
	}catch(std::exception const & e){
		std::cout << "ShaderProgram Exception :: " << e.what() << std::endl;
	}
}

void ShaderProgram::link(){
	try{
		if(device == nullptr)
			throw std::runtime_error("Device is nullptr");
		device->linkProgram(*this);
	}catch(std::exception const & e){
		std::cout << "ShaderProgram Exception :: " << e.what() << std::endl;
	}
}

void ShaderProgram::attach(Shader& s){
	try{
		if(device == nullptr)
			throw std::runtime_error("Device is nullptr");
		device->attachShader(*this, s);
	}catch(std::exception const & e){
		std::cout << "ShaderProgram Exception :: " << e.what() << std::endl;
	}
}

void ShaderProgram::detach(Shader& s){
	try{
		if(device == nullptr)
			throw std::runtime_error("Device is nullptr");
		device->detachShader(*this, s);
	}catch(std::exception const & e){
		std::cout << "ShaderProgram Exception :: " << e.what() << std::endl;
	}		
}

