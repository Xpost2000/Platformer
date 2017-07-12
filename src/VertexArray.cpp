#include "VertexArray.h"
#include "IDevice.h"
#include <iostream>

/*
 * Again use RAII to handle allocation
 * and deallocation
 */

VertexArray::VertexArray(){
	if(obj == 0)
	glGenVertexArrays(1, &obj);
}

VertexArray::~VertexArray(){
	std::cout << "IObjectHandle :: VertexArray :: Destructor()" << std::endl;
	if(obj != 0)
	glDeleteVertexArrays(1, &obj);
}

VertexArray::VertexArray(const std::shared_ptr<IDevice>& dev){
	device = dev;
	if(obj == 0)
	glGenVertexArrays(1, &obj);
}

void VertexArray::set_device(const std::shared_ptr<IDevice> &dev){
	device = dev;
}

void VertexArray::AttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr){
	try{
		if(device == nullptr){
			throw std::runtime_error("IDevice is nullptr");
		}
		device->VertexAttribPointer(index, size, type, normalized, stride, offsetPtr);
	}catch(std::exception const &e){
		std::cout << "Vertex Array Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void VertexArray::EnableAttribute(GLint index){
	try{
		if(device == nullptr){
			throw std::runtime_error("IDevice is nullptr");
		}
		device->EnableAttribute(index);
	}catch(std::exception const &e){
		std::cout << "Vertex Array Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void VertexArray::Bind(){
	device->BindVertexArray(*this);
}

void VertexArray::Unbind(){
	device->UnbindVertexArray();
}

void VertexArray::DrawArrays(DrawMode mode, GLint first, GLint count){
	Bind();
	device->DrawArrays(mode, first, count);
	Unbind();
}

void VertexArray::DrawElements(DrawMode mode, GLint first, GLint count, const GLvoid* indices){
	Bind();
	device->DrawElements(mode, first ,count , indices);
	Unbind();
}
