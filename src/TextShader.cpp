#include "TextShader.h"
#include "mat4.hpp"
#include "ShaderUniform.h"

TextShader::TextShader(const std::shared_ptr<IDevice>& dev) : device(dev){
	vs = new Shader(device, ShaderType::VERTEX);
	fs = new Shader(device, ShaderType::FRAGMENT);
	std::string vert (R"RW(
		#version 330 core
		layout(location=0) in vec4 pos;
		layout(location=1) in vec2 uv;
		layout(location=2) in vec4 clr;
		uniform mat4 proj;
		uniform mat4 view;
		uniform bool transform_with_view=true;
		out vec2 uvCoords;
		out vec4 vColor;

		void main(){
			if(transform_with_view){
				gl_Position = proj*view*vec4(pos.xy, 0, 1);
			}else{
				gl_Position = proj*vec4(pos.xy, 0, 1);
			}
				uvCoords = uv;
				vColor = clr;
		)
	)RW");
	std::string frag (R"RW(
		#version 330 croe
		in vec2 uvCoords;
		in vec4 vColor;
		out vec4 color;
		uniform sampler2D tex;
		void main(){
			vec2 nUvCoords = uvCoords;
			nUvCoords.y = -nUvCoords.y;
			color = vColor*texture(tex, nUvCoords);
		}
	)RW");
	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	sp = new ShaderProgram(device, *vs, *fs);
	sp->link();
	projection_uniform = new ShaderUniform( "proj", *sp );
	view_uniform = new ShaderUniform( "view", *sp );
	view_active_uniform= new ShaderUniform( "transform_with_view" , *sp );
	tex_uniform = new ShaderUniform( "tex", *sp );
}

void TextShader::setTex( int index ){
	tex_uniform->uniformi(index);
}

void TextShader::viewMatrixActive( bool move ){
	view_active_uniform->uniformi(move);
}

void TextShader::SetMatrices( glm::mat4 proj, glm::mat4 view ){
	projection_uniform->uniformMatrix3( 1, false, glm::value_ptr(proj) );
	view_uniform->uniformMatrix3( 1, false, glm::value_ptr(view) );
}

TextShader::~TextShader(){
	delete vs;
	delete fs;
	delete sp;
	delete projection_uniform;
	delete view_uniform;
	delete view_active_uniform;
	delete tex_uniform;
}
