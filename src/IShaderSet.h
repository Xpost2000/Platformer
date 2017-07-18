#ifndef ISHADER_SET_H
#define ISHADER_SET_H
#include "ShaderProgram.h"
#include <iostream>
#include "Shader.h"
/*
 * Interface for "Complete" or "Preset" shaders.
 */
class IShaderSet{
	public:
	void use() { sp->use(); }
	void unuse() { sp->unuse(); }
	protected:
	Shader *vs=nullptr;
	Shader *fs=nullptr;
	ShaderProgram* sp = nullptr;
};

#endif
