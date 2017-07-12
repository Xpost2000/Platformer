#include "GLDevice.h"
#include "VertexArray.h"
#include "Buffer.h"
#include <iostream>

GLDevice::GLDevice() : gl(0){
}

GLDevice::GLDevice(SDL_Window* window, gl_info_struct_t info) : gl(0){
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, info.major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, info.minor);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, info.depth);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, info.stencil);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, info.r_s);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, info.b_s);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, info.g_s);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, info.a_s);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, info.double_buffer);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, info.force_accelerated);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, info.context_type);
		gl = SDL_GL_CreateContext(window);
		glewExperimental = true;
		glewInit();
}


GLDevice::~GLDevice(){
	std::cout << "IDevice :: GLDevice :: Destructor()" << std::endl;
	SDL_GL_DeleteContext(gl);
	gl = 0;
}

std::shared_ptr<VertexArray> GLDevice::GenVertexArray(){
	return std::make_shared<VertexArray>();
}
std::shared_ptr<Buffer> GLDevice::GenBuffer(){
	return std::make_shared<Buffer>();
}
std::shared_ptr<VertexArray> GLDevice::GenVertexArray(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<VertexArray>(dev);
}
std::shared_ptr<Buffer> GLDevice::GenBuffer(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<Buffer>(dev);
}

void GLDevice::BindVertexArray( VertexArray& vao ){
	glBindVertexArray(vao.get_handle());
}

void GLDevice::BindBuffer(Buffer& buf, BufferTypes target){
	glBindBuffer(static_cast<int>(target), buf.get_handle());
}

void GLDevice::UnbindBuffer( BufferTypes target ){
	glBindBuffer(static_cast<int>(target), 0);
}

void GLDevice::UnbindVertexArray(){
	glBindVertexArray(0);
}

void GLDevice::Clear(const BufferClear buf){
	glClear(static_cast<int>(buf));
}

void GLDevice::ClearColor(GLclampf r , GLclampf g , GLclampf b , GLclampf a ){
	glClearColor(r, g, b, a);
}
void GLDevice::ClearAccum(GLclampf r , GLclampf g , GLclampf b , GLclampf a ){
	glClearAccum(r, g, b, a);
}

void GLDevice::ClearDepth(GLfloat value){
	glClearDepthf(value);
}

void GLDevice::ClearStencil(GLint index){
	glClearStencil(index);
}

void GLDevice::DrawArrays( DrawMode m, GLint first, GLint count ){
	glDrawArrays( static_cast<int>(m), first, count );
}
void GLDevice::DrawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices){
	glDrawElements( static_cast<int>(m), first , count , indices );
}

void GLDevice::BufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage ){
//	glBufferData(static_cast<int>(target), sizeof(float)*2, NULL, static_cast<int>(usage));
	glBufferData(static_cast<int>(target), size, data, static_cast<int>(usage));
}

void GLDevice::VertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr){
	
	glVertexAttribPointer(index, size, type, normalized, stride, offsetPtr);
}

void GLDevice::EnableAttribute(GLint index){
	glEnableVertexAttribArray(index);
}

void GLDevice::Viewport(GLuint x, GLuint y, GLuint w, GLuint h){
	glViewport(x, y, w, h);
}

void GLDevice::SetLineWidth(GLuint size){
	glLineWidth(size);
}

void GLDevice::SetPointSize(GLuint size){
	glPointSize(size);
}

bool GLDevice::GetBool(GetParam par){
	unsigned char x;
	glGetBooleanv( static_cast<int>(par) , &x );
	if(x == GL_TRUE)
		return true;
	else{
		return false;
	}
}
int GLDevice::GetInteger(GetParam par){
	int x;
	glGetIntegerv( static_cast<int>(par), &x );
	return x;
}
long GLDevice::GetInteger64(GetParam par){
	long x;
	glGetInteger64v(static_cast<int>(par), &x);
	return x;
}
float GLDevice::GetFloat(GetParam par){
	float x;
	glGetFloatv(static_cast<int>(par), &x);
	return x;
}

void GLDevice::Enable(Feature f){
	glEnable(static_cast<int>(f));
}

void GLDevice::Disable(Feature f){
	glDisable(static_cast<int>(f));
}
