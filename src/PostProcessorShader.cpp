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
		uniform bool shouldFade;
		uniform float dt;
		void main(){
			color = texture(tex, texCoords);
			if(shouldFade){
				if(color.r > 0){
					color -= vec4(dt*20);
				}
			}else{
				color = texture(tex, texCoords);
			}
		}
	)RW");
	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	std::cout << fs->get_log() << std::endl;
	sp = new ShaderProgram(device, *vs, *fs);
	sp->link();
	tex = new ShaderUniform("tex", *sp);
	dt = new ShaderUniform("dt", *sp);
	shouldFade = new ShaderUniform("shouldFade", *sp);
}

PostProcessorShader::~PostProcessorShader(){
	delete vs;
	delete fs;
	delete sp;
	delete tex;
	delete dt;
	delete shouldFade;
}

void PostProcessorShader::setTex(int val){
	tex->uniformi(val);
}
void PostProcessorShader::setFade(bool val){
	shouldFade->uniformi(val);
}
void PostProcessorShader::setDt(float val){
	dt->uniformf(val);
}
