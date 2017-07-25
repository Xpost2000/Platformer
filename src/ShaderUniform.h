#ifndef SHADER_UNIFORM_H
#define SHADER_UNIFORM_H
#include "IObjectHandle.h"
#include <string>
#include "Comparable.h"

class ShaderProgram;
/*
 * This class is a CPU representation of what is a
 * Shader Variable / Shader Uniform.
 *
 * It will gather the location of itself from the name specified
 * and can set it's GPU value to any of your choosing.
 *
 * It just here for abstraction purposes cause it makes more sense to me
 * for many reasons.
 */
class ShaderUniform : public IObjectHandle , public Comparable<ShaderUniform>{
	public:
		ShaderUniform(const ShaderUniform& other) = default;
		ShaderUniform(std::string name, ShaderProgram& prg);	
		ShaderUniform(){}	
		~ShaderUniform(){
			obj = 0;
			self = nullptr;
		}

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

		/*
		 * TODO: Maybe add in overloads to support my math library. Like it's really needed anyways.
		 */
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
