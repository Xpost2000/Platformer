#include "sdl_surface_load_image_wrapper.h"
#include <iostream>

ImageSurface::ImageSurface(const char* path){
	loadImage(path);
}

ImageSurface::~ImageSurface(){
	SDL_FreeSurface(surf);
}

void ImageSurface::loadImage(const char* path){
	surf = IMG_Load(path);
}
