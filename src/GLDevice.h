#ifndef GL_DEVICE_HPP
#define GL_DEVICE_HPP
#include "IDevice.h"
#include <string>
#include "gl_info_struct_t.h"

class GLDevice : public IDevice{
public:
	GLDevice(const GLDevice&) = default;
	GLDevice();
	GLDevice(SDL_Window* window, gl_info_struct_t info);
	~GLDevice();
	
	std::shared_ptr<VertexArray> genVertexArray();
	std::shared_ptr<Buffer> genBuffer();
	std::shared_ptr<Shader> createShader(ShaderType type);
	std::shared_ptr<ShaderProgram> createProgram();

	std::shared_ptr<VertexArray> genVertexArray(const std::shared_ptr<IDevice>& dev);
	std::shared_ptr<Buffer> genBuffer(const std::shared_ptr<IDevice>& dev);
	std::shared_ptr<Shader> createShader(const std::shared_ptr<IDevice>& dev, ShaderType type);
	std::shared_ptr<ShaderProgram> createProgram(const std::shared_ptr<IDevice>& dev);
	std::shared_ptr<ShaderProgram> createProgram(const std::shared_ptr<IDevice>& dev, Shader& a, Shader& b);
	std::shared_ptr<ShaderUniform> createUniform(std::string name, const std::shared_ptr<ShaderProgram>& sp);

	void bindVertexArray( VertexArray& vao );
	void bindBuffer( Buffer& buf, BufferTypes target);
	void unbindBuffer(BufferTypes target);
	void unbindVertexArray();

	void clear(const BufferClear buf);
	void clearColor(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0);
	void clearAccum(GLclampf r = 1.0, GLclampf g = 1.0, GLclampf b = 1.0, GLclampf a = 1.0);
	void clearDepth(GLfloat value);
	void clearStencil(GLint index);

	void drawArrays( DrawMode m, GLint first, GLint count );
	void drawElements( DrawMode m, GLint first, GLint count, const GLvoid* indices );

	void bufferData(const BufferTypes target, size_t size, const GLvoid* data, const BufferUsage usage);
	void vertexAttribPointer(GLuint index, GLint size, GLenum type, bool normalized, GLsizei stride, const GLvoid* offsetPtr);
	void enableAttribute(GLint index);

	void shaderSource(Shader&m, GLsizei, std::string , const GLint*);
	void compileShader(Shader&);

	void detachShader(ShaderProgram&, Shader&);
	void attachShader(ShaderProgram&, Shader&);
	void useProgram(ShaderProgram&);
	void linkProgram(ShaderProgram&);
	void unuseProgram();

	void enable(Feature);
	void disable(Feature);
		
	bool getBool(GetParam);
	int getInteger(GetParam);
	GLint64 getInteger64(GetParam);
	float getFloat(GetParam);
	int getShaderInteger(Shader&, ShaderInfo);
	
	void viewport(GLuint x, GLuint y, GLuint w, GLuint h);
	void setLineWidth(GLuint size);
	void setPointSize(GLuint size);
	DeviceType device_type() { return DeviceType::OPENGL; }
	SDL_GLContext& get_context_gl() { return gl; }
private:
		SDL_GLContext gl;
};

#endif
