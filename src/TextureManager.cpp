#include "TextureManager.h"

std::shared_ptr<ImageTexture> TextureManager::get_tex(std::string key){
	return textures[key];
}

void TextureManager::add_texture(std::string key, std::string directory, const std::shared_ptr<IDevice>& dev){
	textures.insert( std::pair<std::string, std::shared_ptr<ImageTexture> >(key, std::make_shared<ImageTexture>(dev, directory)) );
}
