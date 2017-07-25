#ifndef VERTEX_ARRAY_OBJECT_HPP
#define VERTEX_ARRAY_OBJECT_HPP
#include <memory>
#include "DrawModes.h"
#include "Comparable.h"
#include "IObjectHandle.h"

class IDevice;
/*
 * A OpenGL Vertex Array wrapper.
 * All similar classes require a IDevice ( of type GLDevice preferred since this was primarily made for OpenGL rendering. )
 *
 * I have a few drawing helpers but it's not really needed.
 * All similar classes of this type are also comparable.
 */
class VertexArray : public IObjectHandle, public Comparable<VertexArray>{
	public:
		VertexArray(const VertexArray&) = default;
		VertexArray();
		VertexArray(const std::shared_ptr<IDevice> &dev);
		~VertexArray();
		void set_device(const std::shared_ptr<IDevice> &dev);
		const HandleType is_type() const { return HandleType::HANDLE_VERTEXARRAY; }
		void attribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr);
		void enableAttribute(GLint index);
		void drawArrays(DrawMode mode, GLint first, GLint count);
		void drawElements(DrawMode mode, GLint first, GLint count, const GLvoid* indices);
		void bind();
		void unbind();
// except for the equality operator. All return true since handles aren't exactly numerical and the comparable class is abstract.
	        virtual bool operator >  ( VertexArray rhs )    { return true ;}
	        virtual bool operator <  ( VertexArray rhs )    { return true; }
	        virtual bool operator >= ( VertexArray rhs )  { return true; }
		virtual bool operator <= ( VertexArray rhs )  { return true; }
		virtual bool operator == ( VertexArray rhs )  { return (obj == rhs.obj);}
		const std::shared_ptr<IDevice>& get_device() { return device; }
	private:
		std::shared_ptr<IDevice> device = nullptr;
};

#endif
