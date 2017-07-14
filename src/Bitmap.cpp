#include "Bitmap.h"
#include <GL/glew.h>

Bitmap::Bitmap( void* data, int w, int h, PixelFormat fmt ) : data(data), width(w), height(h), fmt(fmt){
}

Bitmap::Bitmap( int w, int h, PixelFormat fmt ) : data(nullptr) , width(w), height(h), fmt(fmt) {
}

Bitmap::~Bitmap() {
	data = nullptr;
}

int Bitmap::get_format() const{
	switch(fmt){
		case RGB:
			return GL_RGB;
		break;
		case RGBA:
			return GL_RGBA;
		break;
		case BGR:
			return GL_BGR;
		break;
		default:
			return UNKNOWN_FORMAT;
		break;
	}
}

void Bitmap::set_data( void* val ) {
	data = val;
}

void Bitmap::set_width( int w ) {
	width = w;
}

void Bitmap::set_height( int h ) {
	height = h;
}

void* Bitmap::get_data(){
	return data;
}

int Bitmap::get_width() const{
	return width;
}

int Bitmap::get_height() const{
	return height;
}
