#include <iostream>
#include "GLDevice.h"
#include "VertexArray.h"
#include "Buffer.h"

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
	std::shared_ptr<IDevice> ctx = std::make_shared<GLDevice>(window, info);
	std::shared_ptr<Buffer> vbo;
	std::shared_ptr<VertexArray> vao;
	GLfloat vertices[] ={
		-1.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
	        -0.5, 1.0, 0.0	
		,
		0.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		0.5, 1.0, 0.0
	};

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	vbo = ctx->genBuffer(ctx);
	vao = ctx->genVertexArray(ctx);

	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();

	vbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(vertices), vertices, BufferUsage::STATIC_DRAW );
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*3, (const void*)0);
	vao->enableAttribute(0);

	vbo->unbind(BufferTypes::ARRAY_BUFFER);
	vao->unbind();


	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
		}
		ctx->setLineWidth(80);
		ctx->clearColor(0.5, 0.2, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, 1024, 768);

		ctx->bindVertexArray(*vao);
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 6);
		ctx->unbindVertexArray();


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
