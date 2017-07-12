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

	std::cout << "MAJOR : " << ctx->GetInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->GetInteger(GetParam::MINOR_VERSION) << std::endl;
	
	vbo = ctx->GenBuffer(ctx);
	vao = ctx->GenVertexArray(ctx);

	vbo->Bind(BufferTypes::ARRAY_BUFFER);
	vao->Bind();

	vbo->BufferData( BufferTypes::ARRAY_BUFFER, sizeof(vertices), vertices, BufferUsage::STATIC_DRAW );
	vao->AttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*3, (const void*)0);
	vao->EnableAttribute(0);

	vbo->Unbind(BufferTypes::ARRAY_BUFFER);
	vao->Unbind();


	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
		}
		ctx->SetLineWidth(80);
		ctx->ClearColor(0.5, 0.2, 0.3);
		ctx->Clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->Viewport(0, 0, 1024, 768);

		ctx->BindVertexArray(*vao);
		ctx->DrawArrays(DrawMode::TRIANGLES, 0, 6);
		ctx->UnbindVertexArray();


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
