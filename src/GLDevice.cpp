#include "GLDevice.h"
#include "Texture.h"
#include "Renderbuffer.h"
#include "Framebuffer.h"
#include "ShaderProgram.h"
#include "ShaderUniform.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include <iostream>

GLDevice::GLDevice() : gl(0){
}

// I need the editor to figure out it's own dealies.
#ifdef EDITOR_BUILD
GLDevice::GLDevice(SDL_Window* window, gl_info_struct_t info) : gl(0){
}


GLDevice::~GLDevice(){
	std::cout << "IDevice :: GLDevice :: Destructor()" << std::endl;
}
#endif
#ifdef GAME_BUILD
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
#endif

std::shared_ptr<VertexArray> GLDevice::genVertexArray(){
	return std::make_shared<VertexArray>();
}
std::shared_ptr<Buffer> GLDevice::genBuffer(){
	return std::make_shared<Buffer>();
}
std::shared_ptr<Shader> GLDevice::createShader(ShaderType type){
	return std::make_shared<Shader>( type );
}
std::shared_ptr<ShaderProgram> GLDevice::createProgram(){
	return std::make_shared<ShaderProgram>();
}

std::shared_ptr<Renderbuffer> GLDevice::createRenderbuffer(){
	return std::make_shared<Renderbuffer>();
}
std::shared_ptr<Framebuffer> GLDevice::createFramebuffer(){
	return std::make_shared<Framebuffer>();
}
std::shared_ptr<Framebuffer> GLDevice::createFramebuffer(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<Framebuffer>(dev);
}
std::shared_ptr<Renderbuffer> GLDevice::createRenderbuffer(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<Renderbuffer>(dev);
}

std::shared_ptr<ShaderProgram> GLDevice::createProgram( const std::shared_ptr<IDevice>& dev ){
	return std::make_shared<ShaderProgram>(dev);
}

std::shared_ptr<ShaderProgram> GLDevice::createProgram( const std::shared_ptr<IDevice>& dev, Shader& a, Shader& b ){
	return std::make_shared<ShaderProgram>(dev, a, b);
}

std::shared_ptr<Shader> GLDevice::createShader( const std::shared_ptr<IDevice>& dev, ShaderType type ) {
	return std::make_shared<Shader>( dev, type );
}
std::shared_ptr<VertexArray> GLDevice::genVertexArray(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<VertexArray>(dev);
}
std::shared_ptr<Buffer> GLDevice::genBuffer(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<Buffer>(dev);
}

std::shared_ptr<ShaderUniform> GLDevice::createUniform(std::string name, const std::shared_ptr<ShaderProgram>& sp){
	return std::make_shared<ShaderUniform>(name, *sp);
}

std::shared_ptr<Texture> GLDevice::createTexture(){
	return std::make_shared<Texture>();
}
std::shared_ptr<Texture> GLDevice::createTexture(const std::shared_ptr<IDevice>& dev){
	return std::make_shared<Texture>(dev);
}

void GLDevice::bindVertexArray( VertexArray& vao ){
	glBindVertexArray(vao.get_handle());
}

void GLDevice::bindBuffer(Buffer& buf, BufferTypes target){
	glBindBuffer(static_cast<int>(target), buf.get_handle());
}

void GLDevice::unbindBuffer( BufferTypes target ){
	glBindBuffer(static_cast<int>(target), 0);
}

void GLDevice::unbindVertexArray(){
	glBindVertexArray(0);
}

void GLDevice::clear(const BufferClear buf){
	glClear(static_cast<int>(buf));
}

void GLDevice::clearColor(GLclampf r , GLclampf g , GLclampf b , GLclampf a ){
	glClearColor(r, g, b, a);
}
void GLDevice::clearAccum(GLclampf r , GLclampf g , GLclampf b , GLclampf a ){
	glClearAccum(r, g, b, a);
}

void GLDevice::clearDepth(GLfloat value){
	glClearDepthf(value);
}

void GLDevice::clearStencil(GLint index){
	glClearStencil(index);
}

void GLDevice::drawArrays( DrawMode m, GLint first, GLint count ){
	glDrawArrays( static_cast<int>(m), first, count );
}
void GLDevice::drawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices){
	glDrawElements( static_cast<int>(m), first , count , indices );
}

void GLDevice::bufferData( const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage ){
//	glBufferData(static_cast<int>(target), sizeof(float)*2, NULL, static_cast<int>(usage));
	glBufferData(static_cast<int>(target), size, data, static_cast<int>(usage));
}

void GLDevice::bufferSubData( const BufferTypes target, GLintptr offset, GLsizeiptr count, const GLvoid* data ){
	glBufferSubData(static_cast<int>(target), offset, count, data);
}

void GLDevice::vertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr){
	
	glVertexAttribPointer(index, size, type, normalized, stride, offsetPtr);
}

void GLDevice::enableAttribute(GLint index){
	glEnableVertexAttribArray(index);
}

void GLDevice::viewport(GLuint x, GLuint y, GLuint w, GLuint h){
	glViewport(x, y, w, h);
}

void GLDevice::setLineWidth(GLuint size){
	glLineWidth(size);
}

void GLDevice::setPointSize(GLuint size){
	glPointSize(size);
}

bool GLDevice::getBool(GetParam par){
	unsigned char x;
	glGetBooleanv( static_cast<int>(par) , &x );
	if(x == GL_TRUE)
		return true;
	else{
		return false;
	}
}
int GLDevice::getInteger(GetParam par){
	int x;
	glGetIntegerv( static_cast<int>(par), &x );
	return x;
}
// I just realized GLint64 ain't same for all platforms...
GLint64 GLDevice::getInteger64(GetParam par){
	GLint64 x;
	glGetInteger64v(static_cast<int>(par), &x);
	return x;
}
float GLDevice::getFloat(GetParam par){
	float x;
	glGetFloatv(static_cast<int>(par), &x);
	return x;
}

int GLDevice::getShaderInteger( Shader& sh, ShaderInfo type){
	int x;
	glGetShaderiv( sh.get_handle(), static_cast<int>(type), &x);
	return x;
}

void GLDevice::enable(Feature f){
	glEnable(static_cast<int>(f));
}

void GLDevice::disable(Feature f){
	glDisable(static_cast<int>(f));
}

void GLDevice::shaderSource(Shader& m, GLsizei size, std::string str, const GLint* len){
	const char* cstr = str.c_str();
	glShaderSource(m.get_handle(), size, &cstr, len);
}

void GLDevice::compileShader(Shader& m){
	glCompileShader(m.get_handle());
	m.set_compiled(true);
}

void GLDevice::detachShader(ShaderProgram& sp, Shader& s){
	glDetachShader(sp.get_handle(), s.get_handle());
}
void GLDevice::attachShader(ShaderProgram& sp, Shader& s){
	glAttachShader(sp.get_handle(), s.get_handle());
}
void GLDevice::useProgram(ShaderProgram& sp){
	glUseProgram(sp.get_handle());
	sp.set_used(true);
}
void GLDevice::linkProgram(ShaderProgram& sp){
	glLinkProgram(sp.get_handle());
	sp.set_linked(true);
}
// Please prefer to use the visitor interfaces.
// TODO: Fix this.
void GLDevice::unuseProgram(){
	glUseProgram(0);
}

void GLDevice::bindTexture( TextureTarget targ, Texture& tex){
	glBindTexture( static_cast<int>(targ), tex.get_handle() );
}

void GLDevice::unbindTexture( TextureTarget targ ) {
	glBindTexture(static_cast<int>(targ), 0);
}

void GLDevice::texImage2D(TextureTarget targ, GLint level, GLint inFmt, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data){
	glTexImage2D( static_cast<int>(targ), level, inFmt, width, height, border, format, type, data );
}
void GLDevice::textureParameter(TextureTarget targ, TextureParameter param, ParamValue val){
	glTexParameteri( static_cast<int>(targ), static_cast<int>(param), static_cast<int>(val) );
}
void GLDevice::genMipmaps( TextureTarget targ ){
	glGenerateMipmap(static_cast<int>(targ));
}
void GLDevice::bindFramebuffer( FrameBufferTarget fbt, Framebuffer &fb){
	glBindFramebuffer(static_cast<int>(fbt), fb.get_handle());
}
void GLDevice::bindRenderbuffer( Renderbuffer& rb ){
	glBindRenderbuffer( GL_RENDERBUFFER, rb.get_handle() );
}
void GLDevice::unbindFramebuffer( FrameBufferTarget fbt){
	glBindFramebuffer(static_cast<int>(fbt), 0);
}
void GLDevice::unbindRenderbuffer(){
	glBindRenderbuffer( GL_RENDERBUFFER, 0 );
}
void GLDevice::renderBufferStorage( RenderBufferInternalFormat fmt, int w, int h ){
	glRenderbufferStorage( GL_RENDERBUFFER, static_cast<int>(fmt), w, h );
}
// 2D
void GLDevice::frameBufferTexture(FrameBufferTarget rb, FrameBufferAttachment attach, TextureTarget tt, Texture& tex, GLint level ){
	glFramebufferTexture2D( static_cast<int>(rb), static_cast<int>(attach), static_cast<int>(tt), tex.get_handle(), level );
}
void GLDevice::frameBufferRenderbuffer( FrameBufferAttachment attach, Renderbuffer& rbo ){
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, static_cast<int>(attach), GL_RENDERBUFFER, rbo.get_handle() );
}


