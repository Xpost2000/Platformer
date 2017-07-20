#include "ImageTexture.h"
#include "IDevice.h"

ImageTexture::ImageTexture(const std::shared_ptr<IDevice>& dev, const char* path) : device(dev), tex(new Texture(dev)), is(new ImageSurface(path)){
	bm = new Bitmap( is->surf, PixelFormat::RGBA );
	tex->texImage2D(TextureTarget::TEXTURE2D, *bm, 0, 0, GL_UNSIGNED_BYTE);
	tex->textureParameter(TextureTarget::TEXTURE2D, TextureParameter::WRAP_T, ParamValue::REPEAT);
	tex->textureParameter(TextureTarget::TEXTURE2D, TextureParameter::WRAP_S, ParamValue::REPEAT);
	tex->textureParameter(TextureTarget::TEXTURE2D, TextureParameter::MAG_FILTER, ParamValue::NEAREST);
	tex->textureParameter(TextureTarget::TEXTURE2D, TextureParameter::MIN_FILTER, ParamValue::NEAREST);
	device->genMipmaps(TextureTarget::TEXTURE2D);
	tex->unbindTexture(TextureTarget::TEXTURE2D);
}

ImageTexture::~ImageTexture(){
	delete tex;
	delete is;
	delete bm;
}

void ImageTexture::bind(){
	tex->bindTexture(TextureTarget::TEXTURE2D);
}

void ImageTexture::unbind(){
	tex->unbindTexture(TextureTarget::TEXTURE2D);
}
