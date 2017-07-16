#include <GL/glew.h>
#include "Texture.h"
#include <iostream>
#include "Bitmap.h"
#include "IDevice.h"

Texture::Texture(){
	glGenTextures(1, &obj);
}

Texture::Texture(const std::shared_ptr<IDevice>& dev) : device(dev){
	glGenTextures(1, &obj);
}

Texture::~Texture(){
	glDeleteTextures(1, &obj);
}

void Texture::bindTexture( TextureTarget t ){
	try{
	if(device == nullptr)
		throw std::runtime_error("Device is nullptr");
	device->bindTexture(t, *this);
	}catch( const std::exception & e ){
		std::cout << " Texture :: Exception : " << e.what() << std::endl;
	}
}

void Texture::unbindTexture ( TextureTarget t ){
	try{
	if(device == nullptr)
		throw std::runtime_error ("Device is nullptr");
	device->unbindTexture(t);
	}catch( const std::exception& e ){
		std::cout << " Texture :: Exception : " << e.what() << std::endl;
	}
}

void Texture::texImage2D(TextureTarget t, Bitmap& bm, GLint level, GLint border, GLenum type){
	try{
	if(device == nullptr)
		throw std::runtime_error("Device is nullptr");
	bindTexture(t);
	texImage2D(t, level, bm.get_format(), bm.get_width(), bm.get_height(), border, bm.get_format(), type, bm.get_data());
	unbindTexture(t);
	}catch(const std::exception& e ){
		std::cout << " Texture :: Exception : " << e.what() << std::endl;
	}
}

void Texture::texImage2D(TextureTarget t, GLint level, GLint inFmt, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data){
	try{
	if(device == nullptr)
		throw std::runtime_error("Device is nullptr");
	device->texImage2D(t, level, inFmt, width, height, border, format, type, data);
	}catch (const std::exception& e){
		std::cout << "Texture :: Exception : " << e.what() << std::endl;
	}
}
