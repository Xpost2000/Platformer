#ifndef SHADER_UNIFORM_H
#define SHADER_UNIFORM_H
#include "IObjectHandle.h"
#include <string>
#include "Comparable.h"

class ShaderProgram;
class ShaderUniform : public IObjectHandle , public Comparable<ShaderUniform>{
	public:
		ShaderUniform(const ShaderUniform& other) = default;
		ShaderUniform(std::string name, ShaderProgram& prg);	

		const HandleType is_type() const { return HandleType::HANDLE_SHADERUNIFORM; }
		
		GLint get_loc() const;	

		void uniformi(int);
		void uniformi(int, int);
		void uniformi(int, int, int);
		void uniformi(int, int, int , int );

		void uniformf(float);
		void uniformf(float, float);
		void uniformf(float, float, float);
		void uniformf(float, float, float, float);

		void uniformMatrix4(GLsizei, bool transpose, const GLfloat* val);
		void uniformMatrix3(GLsizei, bool transpose, const GLfloat* val);

		bool is_valid() { return (obj != -1); }	
		bool operator > ( ShaderUniform rhs ) { return true; } 
		bool operator < ( ShaderUniform rhs ) { return true; } 
		bool operator >= ( ShaderUniform rhs ) { return true; } 
		bool operator <= ( ShaderUniform rhs ) { return true; } 
		bool operator == ( ShaderUniform rhs ) { return (obj == rhs.obj);} 
	private:
		std::string name;
		ShaderProgram* self = nullptr;
};

#endif
