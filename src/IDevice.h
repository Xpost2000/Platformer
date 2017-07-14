#ifndef INTERFACE_DEVICE_HPP
#define INTERFACE_DEVICE_HPP
#include <memory>
#include "GetParam.h"
#include "TextureParameter.h"
#include "Feature.h"
#include "DrawModes.h"
#include "ShaderInfo.h"
#include "DeviceTypes.h"
#include "Bitmap.h"
#include "BufferUsage.h"
#include <SDL2/SDL.h>
#include "BufferTypes.h"
#include "BufferClearTypes.h"
// TODO INCLUDE DX HEADERS
/*
 * This class is another abstract class.
 * It's a generic interface for Graphical Context.
 * Primarily ment for OpenGL ( hence the opengl function names ),
 * however if adapted properly may be used for DirectX
 * (It's a lot of work to port over since I use OpenGL int constants and enums for alot of things here. )
 *
 * The interface functions are named similar to their OpenGL types.
 *
 * it's a One to One mapping.
 * eg : Clear = glClear
 * 	ClearColor = glClearColor
 * This wrapper is more typesafe and very easy to use.
 *
 */
// forward declarations here

class VertexArray;
class Buffer;
class Shader;
class ShaderProgram;
class ShaderUniform;
class Texture;

// class
class IDevice{
	public:
//		IDevice(){}
//		~IDevice(){}
//
//		Create functions functions.
		virtual std::shared_ptr<VertexArray> genVertexArray() = 0;
		virtual std::shared_ptr<Buffer> genBuffer() = 0;
		virtual std::shared_ptr<Shader> createShader( ShaderType type ) = 0;
		virtual std::shared_ptr<ShaderProgram> createProgram() = 0;
		virtual std::shared_ptr<Texture> createTexture() = 0;

		virtual std::shared_ptr<VertexArray> genVertexArray(const std::shared_ptr<IDevice>& dev) = 0;
		virtual std::shared_ptr<Texture> createTexture(const std::shared_ptr<IDevice>& dev) = 0;
		virtual std::shared_ptr<Buffer> genBuffer(const std::shared_ptr<IDevice>& dev) = 0;
		virtual std::shared_ptr<Shader> createShader( const std::shared_ptr<IDevice>& dev, ShaderType type ) = 0;
		virtual std::shared_ptr<ShaderProgram> createProgram( const std::shared_ptr<IDevice>& dev ) = 0;
		virtual std::shared_ptr<ShaderProgram> createProgram(const std::shared_ptr<IDevice>& dev, Shader& a, Shader& b) = 0;
		virtual std::shared_ptr<ShaderUniform> createUniform(std::string name, const std::shared_ptr<ShaderProgram>& sp) = 0;
		// Binding Functions
		virtual void bindVertexArray( VertexArray& vao ) = 0;
		virtual void bindBuffer( Buffer& buf, BufferTypes target) = 0;
		virtual void unbindBuffer( BufferTypes target ) = 0 ;
		virtual void unbindVertexArray( ) = 0;
		virtual void bindTexture( TextureTarget targ, Texture& tex ) = 0; 
		virtual void unbindTexture( TextureTarget targ ) = 0;
		// Clear Functions
		virtual void clear(const BufferClear buf) = 0;
		virtual void clearColor(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0) = 0;
		virtual void clearAccum(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0) = 0;
		virtual void clearDepth(GLfloat value) = 0;
		virtual void clearStencil(GLint index) = 0;
		// Draw
		virtual void drawArrays( DrawMode m, GLint first, GLint count ) = 0;
		virtual void drawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices) = 0;
		// Shader Related Functions
		
		// Texture stuff
		virtual void texImage2D(TextureTarget targ, GLint level, GLint inFmt, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data) = 0;	
		virtual void textureParameter(TextureTarget targ, TextureParameter param, ParamValue val) = 0;
		virtual void genMipmaps(TextureTarget targ) = 0;
		// Data init functions
		virtual void bufferData(const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage) = 0;
		virtual void vertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr) = 0;
		virtual void enableAttribute(GLint index) = 0;
		virtual void shaderSource(Shader&, GLsizei, std::string , const GLint*) = 0;
		virtual void compileShader(Shader&) = 0;

		virtual void detachShader(ShaderProgram&, Shader&) = 0;
		virtual void attachShader(ShaderProgram&, Shader&) = 0;
		virtual void useProgram(ShaderProgram&) = 0;
		virtual void linkProgram(ShaderProgram&) = 0;
		virtual void unuseProgram() = 0;


		// Get
		
		virtual bool getBool(GetParam) = 0;
		virtual int getInteger(GetParam) = 0;
		virtual GLint64 getInteger64(GetParam) = 0;
		virtual float getFloat(GetParam) = 0;
		virtual int getShaderInteger(Shader&, ShaderInfo) = 0;
		
		
		//Enable
		virtual void enable(Feature) = 0;
		virtual void disable(Feature) = 0;
		// etc.
		virtual void viewport(GLuint x, GLuint y, GLuint w, GLuint h) = 0;	
		virtual void setLineWidth(GLuint size) = 0;
		virtual void setPointSize(GLuint size) = 0;
		virtual DeviceType device_type() = 0;
		// context
		virtual SDL_GLContext& get_context_gl() = 0;
	protected:
};

#endif
