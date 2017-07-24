#include "LightShader.h"
#include "mat4.hpp"

LightShader::LightShader(const std::shared_ptr<IDevice>& dev) :device(dev){
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
		out vec2 pos;
		out vec4 vColor;

		void main(){
			gl_Position = proj*view*vec4(position.xy, 0.0 , 1.0);
			uvCoords = uv;
			vColor = color;
			pos = vec2(position.x, position.y);
		}
	)RW");
	std::string frag(R"RW(
		#version 330 core
		uniform sampler2D tex;
		in vec2 uvCoords;
		in vec4 vColor;
		in vec2 pos;
		out vec4 color;
		uniform bool textured;

		const int MAX_LIGHTS = 10;
		uniform vec2 lightPos[MAX_LIGHTS];
		uniform vec3 lightColor[MAX_LIGHTS];
		uniform float power[MAX_LIGHTS];
		vec3 ambient;

		void main(){
			if(textured)
			color = vColor*texture(tex, uvCoords);
			else
			color = vColor;

			ambient = vec3(0.2);
			vec4 res = vec4(ambient, 1.0f); 
			for(int i = 0; i < MAX_LIGHTS; i++){
				vec4 t = vec4(ambient, 1.0);
				float intensity = 0.8/length(pos-lightPos[i]);
				t *= vec4((intensity*lightColor[i].x)*power[i], (intensity*lightColor[i].y)*power[i], (intensity*lightColor[i].z)*power[i], 1);
				res += t; // add the result ( do each lighting pass individually then add back on. )
			}
				color *= res;
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
	std::cout << "FS\n";
	std::cout << fs->get_log() << std::endl;

	for(int i = 0; i < 10; ++i){
		lightPos[i] = ShaderUniform("lightPos[" + std::to_string(i) + "]", *sp);
		lightColor[i] = ShaderUniform("lightColor[" + std::to_string(i) + "]", *sp);
		lightPower[i] = ShaderUniform("power[" + std::to_string(i) + "]", *sp);
	}

}

LightShader::~LightShader(){
	delete tex;
	delete projMat;
	delete viewMat;
	delete textured;
	delete vs;
	delete fs;
	delete sp;
}


void LightShader::setTex(int x){
	tex->uniformi(x);
}
void LightShader::setTextured(bool v){
	textured->uniformi(v);
}
void LightShader::setView(glm::mat4 m){
	viewMat->uniformMatrix4(1, false, glm::value_ptr(m));
}
void LightShader::setProj(glm::mat4 m){
	projMat->uniformMatrix4(1, false, glm::value_ptr(m));
}

void LightShader::setLight(int index, Light l){
	lightPos[index].uniformf( l.pos.x(), l.pos.y() );
	lightColor[index].uniformf(l.color.r(), l.color.b(), l.color.g());
	lightPower[index].uniformf( l.strength ); 
}
