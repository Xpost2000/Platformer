#ifndef SHADER_H
#define SHADER_H
#include "IObjectHandle.h"
#include "Comparable.h"
#include "ShaderInfo.h"
#include <memory>

class IDevice;
class Shader : public IObjectHandle, public Comparable<Shader>{
	public:
	Shader(const Shader& other) = default;
	Shader(const std::shared_ptr<IDevice> & dev, ShaderType type);
	Shader( ShaderType type );
	~Shader();

	const HandleType is_type() const { return HandleType::HANDLE_SHADER; }	
	void compile();
	void source(GLsizei, std::string, const GLint*);
	std::string get_log();
	/*
	 * Empty function prototypes.
	 * Because these are the amount of functions I estimate will work.
	 */

	bool is_compiled() {return compiled;}
	void set_compiled(bool v) { compiled = v;}
	bool operator >  ( Shader rhs ) { return true; }
	bool operator <  ( Shader rhs ) { return true; }
	bool operator >= ( Shader rhs ) { return true; }
	bool operator <= ( Shader rhs ) { return true; }
	bool operator == ( Shader rhs ) { return (obj == rhs.obj);}
	private:
	std::shared_ptr<IDevice> device = nullptr;
	bool compiled;
};

#endif
