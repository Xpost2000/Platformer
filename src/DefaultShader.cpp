#include "DefaultShader.h"
#include <iostream>
#include "ShaderUniform.h"
#include "mat4.hpp"

DefaultShader::DefaultShader(const std::shared_ptr<IDevice>& dev) : device(dev){
	vs = new Shader(device, ShaderType::VERTEX);
	fs = new Shader(device, ShaderType::FRAGMENT);
	std::string vert(R"RW(
		#version 330 core
		layout(location=0) in vec3 position;
		layout(location=1) in vec2 uv;
		layout(location=2) in vec4 color;
		uniform mat4 proj;
		uniform mat4 view;
		out vec2 uvCoords;
		out vec4 vColor;
		void main(){
			gl_Position = proj*view*vec4(position.xy, 0.0 , 1.0);
			uvCoords = uv;
			vColor = color;
		}
	)RW");
	std::string frag(R"RW(
		#version 330 core
		uniform sampler2D tex;
		in vec2 uvCoords;
		in vec4 vColor;
		out vec4 color;
		uniform bool textured;
		void main(){
			if(textured)
			color = vColor*texture(tex, uvCoords);
			else
			color = vColor;
		}
	)RW");
	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	sp = new ShaderProgram(device, *vs, *fs);
	sp->link();
	projMat = new ShaderUniform("proj", *sp);
	viewMat = new ShaderUniform("view", *sp);
	tex = new ShaderUniform("tex", *sp);
	textured = new ShaderUniform("textured", *sp);
	std::cout << vs->get_log() << std::endl;
	std::cout << fs->get_log() << std::endl;
}

DefaultShader::~DefaultShader(){
	delete sp;
	delete vs;
	delete fs;
	delete tex;
	delete textured;
	delete projMat;
        delete viewMat;	
}


void DefaultShader::setTextured(bool v){
	textured->uniformi(v);
}

void DefaultShader::setTex(int v){
	tex->uniformi(v);
}
void DefaultShader::setMatrices(Matrix4f p, Matrix4f v){
	projMat->uniformMatrix4(1, false, p.data());
	viewMat->uniformMatrix4(1, false, v.data());
}
void DefaultShader::setMatrices(glm::mat4 p, glm::mat4 v){
	projMat->uniformMatrix4(1, false, glm::value_ptr(p));
	viewMat->uniformMatrix4(1, false, glm::value_ptr(v));
}
