#include "Bitmap.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

/*
 * Implementation file
 */

Bitmap::Bitmap( SDL_Surface* s, PixelFormat fmt) : Bitmap(s->pixels, s->w, s->h, fmt){
}

Bitmap::Bitmap( void* data, int w, int h, PixelFormat fmt ) : data(data), width(w), height(h), fmt(fmt){
}

Bitmap::Bitmap( int w, int h, PixelFormat fmt ) : data(nullptr) , width(w), height(h), fmt(fmt) {
}

Bitmap::~Bitmap() {
	data = nullptr;
}
/*
 * What I do here is that I use a switch statement to check the value of the enum
 * I return the cooresponding GLenum.
 */
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
