#include "PostProcessorShader.h"
#include "ShaderUniform.h"

PostProcessorShader::PostProcessorShader(const std::shared_ptr<IDevice>& dev) : device(dev){
	vs = new Shader(device, ShaderType::VERTEX);
	fs = new Shader(device, ShaderType::FRAGMENT);
	std::string vert(R"RW(
		#version 330 core
		layout(location=0) in vec3 pos;
		layout(location=1) in vec2 tc;
		out vec2 texCoords;
		void main(){
			gl_Position = vec4(pos, 1.0f);
			texCoords = tc;
		}
	)RW");
	std::string frag(R"RW(
		#version 330 core
		uniform sampler2D tex;
		in vec2 texCoords;
		out vec4 color;
		void main(){
			color = texture(tex, texCoords);
		}
	)RW");
	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	sp = new ShaderProgram(device, *vs, *fs);
	sp->link();
	tex = new ShaderUniform("tex", *sp);
}

PostProcessorShader::~PostProcessorShader(){
	delete vs;
	delete fs;
	delete sp;
	delete tex;
}

void PostProcessorShader::setTex(int val){
	tex->uniformi(val);
}
