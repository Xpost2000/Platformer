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

void VertexArray::attribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr){
	try{
		if(std::is_null_pointer< decltype(device) >::value){
			throw std::runtime_error("IDevice is nullptr");
		}
		device->vertexAttribPointer(index, size, type, normalized, stride, offsetPtr);
	}catch(std::exception const &e){
		std::cout << "Vertex Array Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void VertexArray::enableAttribute(GLint index){
	try{
		if(std::is_null_pointer< decltype(device) >::value){
			throw std::runtime_error("IDevice is nullptr");
		}
		device->enableAttribute(index);
	}catch(std::exception const &e){
		std::cout << "Vertex Array Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void VertexArray::bind(){
	device->bindVertexArray(*this);
}

void VertexArray::unbind(){
	device->unbindVertexArray();
}

void VertexArray::drawArrays(DrawMode mode, GLint first, GLint count){
	bind();
	device->drawArrays(mode, first, count);
	unbind();
}

void VertexArray::drawElements(DrawMode mode, GLint first, GLint count, const GLvoid* indices){
	bind();
	device->drawElements(mode, first ,count , indices);
	unbind();
}
