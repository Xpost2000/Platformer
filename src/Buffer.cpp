#include "Buffer.h"
#include <iostream>
#include "IDevice.h"

/*
 * Handle RAII for stuff.
 *
 * These classes are ment to be used with smart pointers.
 */

Buffer::Buffer(const std::shared_ptr<IDevice>& dev){
	device = dev;
	if(obj == 0)
	glGenBuffers(1, &obj);
}

Buffer::Buffer(){
	if(obj == 0)
	glGenBuffers(1, &obj);
}

Buffer::~Buffer(){
	std::cout << "IObjectHandle :: Buffer :: Destructor()" << std::endl;
	if(obj != 0)
	glDeleteBuffers(1, &obj);
}

void Buffer::set_device(const std::shared_ptr<IDevice>& dev){
	device = dev;
}

void Buffer::Bind(const BufferTypes target){
	try{
	if(device == nullptr){
		throw std::runtime_error("IDevice is a nullptr.... Violation error would occur here.");
	}
	device->BindBuffer(*this, target);
	}
	catch(std::exception const &e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void Buffer::Unbind(const BufferTypes target){
try{
	if(device == nullptr){
		throw std::runtime_error("IDevice is a nullptr.... Violation error");	
	}
	device->UnbindBuffer(target);
	}catch(std::exception const& e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}
void Buffer::BufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage ){
	try{
	if(device == nullptr){
		throw std::runtime_error("IDevice is a nullptr");
	}
	device->BufferData(target, size, data, usage);
	}catch(std::exception const& e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}
