#ifndef COMPLETE_IMAGE_TEXTURE_WRAPPER_H
#define COMPLETE_IMAGE_TEXTURE_WRAPPER_H
#include <string>
#include "Texture.h"
#include "Bitmap.h"
#include "sdl_surface_load_image_wrapper.h"

/*
 * Like many other things this is a convience wrapper.
 * Loads an image to a bitmap.
 * Sets up a texture and completes the texture with the bitmap.
 *
 * It will load an image surface and put the pixels on a bitmap
 */
class IDevice;
class ImageTexture{
	public:
		ImageTexture( ){}
		ImageTexture( const std::shared_ptr<IDevice>& dev , std::string fPath );
		~ImageTexture();
		Texture& get() { return *tex; } // incase you actually want to manually do something
		void bind();
		void unbind();
	private:
		ImageSurface* is = nullptr;
		Bitmap* bm = nullptr;
		Texture* tex = nullptr;
		std::shared_ptr<IDevice> device = nullptr;
};
#endif
