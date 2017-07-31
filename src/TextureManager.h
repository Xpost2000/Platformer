#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <map>
#include <memory>
#include "ImageTexture.h"
#include "IDevice.h"
class TextureManager{
	public:
		std::shared_ptr<ImageTexture> get_tex(std::string key);
		void add_texture(std::string key, std::string directory, const std::shared_ptr<IDevice>& dev);
	private:
		std::map<std::string, std::shared_ptr<ImageTexture> > textures;
};
#endif
