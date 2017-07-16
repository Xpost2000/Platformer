#include "Renderbuffer.h"

Renderbuffer::Renderbuffer(){
	glGenRenderbuffers(1, &obj);
}

Renderbuffer::~Renderbuffer(){
	glDeleteRenderbuffers(1, &obj);
}
