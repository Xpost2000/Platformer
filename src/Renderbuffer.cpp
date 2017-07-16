#include "Renderbuffer.h"
#include "IDevice.h"

Renderbuffer::Renderbuffer (const std::shared_ptr<IDevice>& dev): device(dev){
	glGenRenderbuffers(1, &obj);
}

Renderbuffer::Renderbuffer() :  device(nullptr){
	glGenRenderbuffers(1, &obj);
}

Renderbuffer::~Renderbuffer(){
	glDeleteRenderbuffers(1, &obj);
}
