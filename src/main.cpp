#include <iostream>
/*
#include "GLDevice.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderUniform.h"
#include "VertexArray.h"
#include "Buffer.h"
*/
#include "typedefs.h"

std::string vert ( R"RW(
	#version 330 core
	layout(location=0) in vec3 pos;
	layout(location=1) in vec3 clr;
	out vec3 vClr;
	void main(){
		gl_Position = vec4(pos, 1.0f);
		vClr = clr;
	}
)RW");
std::string frag(R"RW(
	#version 330 core
	in vec3 vClr;
	out vec4 color;
	uniform float d;
	void main(){
		color = vec4(vClr.r - d, vClr.g - d, vClr.b - d, 1.0f);	
	}
)RW");

int main(int argc, char** argv){
	SDL_Window* window;
	SDL_Event ev;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test Letter X OGL Wrapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1024, 768, SDL_WINDOW_OPENGL);
	gl_info_struct_t info = {
		3,
		3,
		24,
		16,
		24,
		24,
		24,
		24,
		true,
		true,
		CORE_CONTEXT
	};
	core::IDevice ctx = std::make_shared<GLDevice>(window, info);
	core::Buffer vbo;
	core::VertexArray vao;
	core::Shader vs, fs;
	core::ShaderProgram sp;
	core::ShaderUniform d;
	GLfloat vertices[] ={
		-1.0, -1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 0.0, 1.0
	};

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	vbo = ctx->genBuffer(ctx);
	vao = ctx->genVertexArray(ctx);

	vs = ctx->createShader(ctx, ShaderType::VERTEX);
	fs = ctx->createShader(ctx, ShaderType::FRAGMENT);

	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	
	sp = ctx->createProgram(ctx, *vs, *fs);
	sp->link();
	d = ctx->createUniform("d", sp); 

	std::cout << vs->get_log() << std::endl;

	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();

	vbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(vertices), vertices, BufferUsage::STATIC_DRAW );
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*6, (const void*)0);
	vao->attribPointer(1, 3, GL_FLOAT, false, sizeof(float)*6, (const void*)(sizeof(float)*3));
	vao->enableAttribute(1);
	vao->enableAttribute(0);

	vbo->unbind(BufferTypes::ARRAY_BUFFER);
	vao->unbind();


	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
		}
		sp->use();
		d->uniformf(.7f);
		ctx->setLineWidth(80);
		ctx->clearColor(0.5, 0.2, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, 1024, 768);

		ctx->bindVertexArray(*vao);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);
		ctx->unbindVertexArray();


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
