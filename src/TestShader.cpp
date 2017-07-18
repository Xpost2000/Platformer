#include "TestShader.h"
#include "mat4.hpp"
#include "ShaderUniform.h"

TestShader::TestShader(const std::shared_ptr<IDevice>& dev) : device(dev){
	vs = new Shader(device, ShaderType::VERTEX);
	fs = new Shader(device, ShaderType::FRAGMENT);
	std::string vert (R"RW(
		#version 330 core
		layout(location=0) in vec3 pos;
		layout(location=1) in vec2 clr;
		layout(location=2) in vec3 fst;
		out vec2 vClr;
		out vec3 vFst;
		uniform mat4 model;
		void main(){
			gl_Position = model*vec4(pos, 1.0f);
			vClr = clr;
			vFst = fst;
		}
	)RW");
	std::string frag (R"RW(
		#version 330 core
		uniform sampler2D tex;
		in vec2 vClr;
		in vec3 vFst;
		out vec4 color;
		uniform float d;
		void main(){
			color = texture(tex, vClr);
			color *= vec4(d);
			color += vec4(vFst, 1.0f);
		}
	)RW");
	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	sp = new ShaderProgram(device, *vs, *fs);
	sp->link();
	d = new ShaderUniform("d", *sp);
	matrix = new ShaderUniform("model", *sp);
	tex = new ShaderUniform("tex", *sp);
}

TestShader::~TestShader(){
	delete vs;
	delete fs;
	delete sp;
	delete d;
	delete tex;
	delete matrix;
}

void TestShader::setD(float val){
	d->uniformf(val);
}

void TestShader::setMatrix(Matrix4f mat){
	matrix->uniformMatrix4(1, false, mat.data());
}
void TestShader::setTex(int val){
	tex->uniformi(val);
}
