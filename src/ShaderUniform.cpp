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
	self->use();
	glUniform1i( obj, v0 );
}
void ShaderUniform::uniformi(int v0 , int v1){
	self->use();
	glUniform2i(obj, v0, v1);
}
void ShaderUniform::uniformi(int v0, int v1, int v2){
	self->use();
	glUniform3i(obj, v0, v1, v2);
}
void ShaderUniform::uniformi(int v0, int v1, int v2, int v3){
	self->use();
	glUniform4i(obj, v0, v1, v2, v3);
}

void ShaderUniform::uniformf(float v0){
	self->use();
	glUniform1f(obj, v0);
}
void ShaderUniform::uniformf(float v0 , float v1){
	self->use();
	glUniform2f(obj, v0, v1);
}
void ShaderUniform::uniformf(float v0 , float v1, float v2){
	self->use();
	glUniform3f(obj, v0, v1, v2);
}
void ShaderUniform::uniformf(float v0, float v1, float v2, float v3){
	self->use();
	glUniform4f(obj, v0, v1, v2, v3);
}

void ShaderUniform::uniformMatrix4(GLsizei count, bool transpose, const GLfloat* val){
	self->use();
	glUniformMatrix4fv(obj, count, transpose, val);
}
void ShaderUniform::uniformMatrix3(GLsizei count, bool transpose, const GLfloat* val){
	self->use();
	glUniformMatrix3fv(obj, count, transpose, val);
}
