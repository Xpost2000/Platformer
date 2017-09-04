#ifndef SDL_SURFACE_LOAD_IMG_WRAPPER
#define SDL_SURFACE_LOAD_IMG_WRAPPER

/*
 * I didn't want to deallocate memory myself. So I made 
 * a RAII wrapper to do it for me.
 *
 * It quickly loads an image to an SDL struct and allows easy access
 * to the pixels.
 */

#include <SDL2/SDL_image.h>
struct ImageSurface{
	ImageSurface( const char* path );
	~ImageSurface();
	void loadImage( const char* path );
	SDL_Surface* surf = nullptr;
};

#endif
