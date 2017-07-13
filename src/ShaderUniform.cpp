#include "ShaderUniform.h"
#include "ShaderProgram.h"

ShaderUniform::ShaderUniform(std::string name, ShaderProgram& prg){
	this->name = name;
	self = &prg;
	obj = glGetUniformLocation(self->get_handle(), name.c_str());
}

GLint ShaderUniform::get_loc()const{
	return glGetUniformLocation(self->get_handle(), name.c_str());
}

void ShaderUniform::uniformi(int v0){
	glUniform1i( obj, v0 );
}
void ShaderUniform::uniformi(int v0 , int v1){
	glUniform2i(obj, v0, v1);
}
void ShaderUniform::uniformi(int v0, int v1, int v2){
	glUniform3i(obj, v0, v1, v2);
}
void ShaderUniform::uniformi(int v0, int v1, int v2, int v3){
	glUniform4i(obj, v0, v1, v2, v3);
}

void ShaderUniform::uniformf(float v0){
	glUniform1f(obj, v0);
}
void ShaderUniform::uniformf(float v0 , float v1){
	glUniform2f(obj, v0, v1);
}
void ShaderUniform::uniformf(float v0 , float v1, float v2){
	glUniform3f(obj, v0, v1, v2);
}
void ShaderUniform::uniformf(float v0, float v1, float v2, float v3){
	glUniform4f(obj, v0, v1, v2, v3);
}

void ShaderUniform::uniformMatrix4(GLsizei count, bool transpose, const GLfloat* val){
	glUniformMatrix4fv(obj, count, transpose, val);
}
void ShaderUniform::uniformMatrix3(GLsizei count, bool transpose, const GLfloat* val){
	glUniformMatrix3fv(obj, count, transpose, val);
}
