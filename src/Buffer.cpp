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
	if(!obj)
	glGenBuffers(1, &obj);
}

Buffer::Buffer() {
	if(!obj)
	glGenBuffers(1, &obj);
}

Buffer::~Buffer(){
	std::cout << "IObjectHandle :: Buffer :: Destructor()" << std::endl;
	if(obj)
	glDeleteBuffers(1, &obj);
}

void Buffer::set_device(const std::shared_ptr<IDevice>& dev){
	device = dev;
}

/*
 * All the classes below are self explainatory.
 * These classes all throw exceptions mainly because
 * in the case that the device is equal to a nullptr
 * we will at least detect it.
 */

void Buffer::bind(const BufferTypes target){
	try{
		// using type_traits for more logically readable code.
	if(std::is_null_pointer< decltype(device) >::value){
		throw std::runtime_error("IDevice is a nullptr.... Violation error would occur here.");
	}
	device->bindBuffer(*this, target);
	}
	catch(std::exception const &e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}

void Buffer::unbind(const BufferTypes target){
try{
	if(std::is_null_pointer< decltype(device) >::value){
		throw std::runtime_error("IDevice is a nullptr.... Violation error");	
	}
	device->unbindBuffer(target);
	}catch(std::exception const& e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}
void Buffer::bufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage ){
	try{
	if(std::is_null_pointer< decltype(device) >::value){
		throw std::runtime_error("IDevice is a nullptr");
	}
	device->bufferData(target, size, data, usage);
	}catch(std::exception const& e){
		std::cout << "Buffer Object Exception :: " << e.what() << std::endl;
		exit(-1);
	}
}
