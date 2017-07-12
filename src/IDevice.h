#ifndef INTERFACE_DEVICE_HPP
#define INTERFACE_DEVICE_HPP
#include <memory>
#include "GetParam.h"
#include "DrawModes.h"
#include "DeviceTypes.h"
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

// class
class IDevice{
	public:
//		IDevice(){}
//		~IDevice(){}
//
//		Create functions functions.
		virtual std::shared_ptr<VertexArray> GenVertexArray() = 0;
		virtual std::shared_ptr<Buffer> GenBuffer() = 0;

		virtual std::shared_ptr<VertexArray> GenVertexArray(const std::shared_ptr<IDevice>& dev) = 0;
		virtual std::shared_ptr<Buffer> GenBuffer(const std::shared_ptr<IDevice>& dev) = 0;
		// Binding Functions
		virtual void BindVertexArray( VertexArray& vao ) = 0;
		virtual void BindBuffer( Buffer& buf, BufferTypes target) = 0;
		virtual void UnbindBuffer( BufferTypes target ) = 0 ;
		virtual void UnbindVertexArray( ) = 0;
		// Clear Functions
		virtual void Clear(const BufferClear buf) = 0;
		virtual void ClearColor(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0) = 0;
		virtual void ClearAccum(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0) = 0;
		virtual void ClearDepth(GLfloat value) = 0;
		virtual void ClearStencil(GLint index) = 0;
		// Draw
		virtual void DrawArrays( DrawMode m, GLint first, GLint count ) = 0;
		virtual void DrawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices) = 0;
		
		// Data init functions
		virtual void BufferData(const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage) = 0;
		virtual void VertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr) = 0;
		virtual void EnableAttribute(GLint index) = 0;
		// Get
		
		virtual bool GetBool(GetParam) = 0;
		virtual int GetInteger(GetParam) = 0;
		virtual long GetInteger64(GetParam) = 0;
		virtual float GetFloat(GetParam) = 0;
		
		// etc.
		virtual void Viewport(GLuint x, GLuint y, GLuint w, GLuint h) = 0;	
		virtual void SetLineWidth(GLuint size) = 0;
		virtual void SetPointSize(GLuint size) = 0;
		virtual DeviceType device_type() = 0;
		// context
		virtual SDL_GLContext& get_context_gl() = 0;
	protected:
};

#endif
