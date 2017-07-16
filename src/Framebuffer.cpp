#include "Framebuffer.h"
#include "IDevice.h"

Framebuffer::Framebuffer(const std::shared_ptr<IDevice>& dev) : device(dev){
	glGenFramebuffers(1, &obj);
}

Framebuffer::Framebuffer() : device(nullptr){
	glGenFramebuffers(1, &obj);
}

Framebuffer::~Framebuffer(){
	glDeleteFramebuffers( 1, &obj );
}
