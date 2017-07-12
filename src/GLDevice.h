#ifndef GL_DEVICE_HPP
#define GL_DEVICE_HPP
#include "IDevice.h"
#include "gl_info_struct_t.h"

class GLDevice : public IDevice{
public:
	GLDevice(const GLDevice&) = default;
	GLDevice();
	GLDevice(SDL_Window* window, gl_info_struct_t info);
	~GLDevice();
	
	std::shared_ptr<VertexArray> GenVertexArray();
	std::shared_ptr<Buffer> GenBuffer();

	std::shared_ptr<VertexArray> GenVertexArray(const std::shared_ptr<IDevice>& dev);
	std::shared_ptr<Buffer> GenBuffer(const std::shared_ptr<IDevice>& dev);
	void BindVertexArray( VertexArray& vao );
	void BindBuffer( Buffer& buf, BufferTypes target);
	void UnbindBuffer(BufferTypes target);
	void UnbindVertexArray();

	void Clear(const BufferClear buf);
	void ClearColor(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0);
	void ClearAccum(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0);
	void ClearDepth(GLfloat value);
	void ClearStencil(GLint index);

	void DrawArrays( DrawMode m, GLint first, GLint count );
	void DrawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices );

	void BufferData(const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage);
	void VertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr);
	void EnableAttribute(GLint index);

	void Enable(Feature);
	void Disable(Feature);
		
	bool GetBool(GetParam);
	int GetInteger(GetParam);
	long GetInteger64(GetParam);
	float GetFloat(GetParam);
	
	void Viewport(GLuint x, GLuint y, GLuint w, GLuint h);
	void SetLineWidth(GLuint size);
	void SetPointSize(GLuint size);
	DeviceType device_type() { return DeviceType::OPENGL; }
	SDL_GLContext& get_context_gl() { return gl; }
private:
		SDL_GLContext gl;
};

#endif
