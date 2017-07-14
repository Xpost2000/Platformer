#include <GL/glew.h>
#include "Texture.h"
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
