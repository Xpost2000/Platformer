#include "Framebuffer.h"

Framebuffer::Framebuffer(){
	glGenFramebuffers(1, &obj);
}

Framebuffer::~Framebuffer(){
	glDeleteFramebuffers( 1, &obj );
}
