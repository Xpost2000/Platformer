#include "DefaultShader.h"
#include "mat4.hpp"
#include "ShaderUniform.h"

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
			gl_Position = proj*view*vec4(position, 1.0f);
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
		void main(){
			color = texture(tex, uvCoords);
			color *= vColor;	
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
}

DefaultShader::~DefaultShader(){
	delete sp;
	delete vs;
	delete fs;
	delete tex;
	delete projMat;
        delete viewMat;	
}

void DefaultShader::setTex(int v){
	tex->uniformi(v);
}
void DefaultShader::setMatrices(Matrix4f p, Matrix4f v){
	projMat->uniformMatrix4(1, false, p.data());
	viewMat->uniformMatrix4(1, false, v.data());
}
