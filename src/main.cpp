#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>
#include "typedefs.h"

std::string vert ( R"RW(
	#version 330 core
	layout(location=0) in vec3 pos;
	layout(location=1) in vec2 clr;
	out vec2 vClr;
	void main(){
		gl_Position = vec4(pos, 1.0f);
		vClr = clr;
	}
)RW");
std::string frag(R"RW(
	#version 330 core
	uniform sampler2D tex;
	in vec2 vClr;
	out vec4 color;
	uniform float d;
	void main(){
		color = texture(tex, vClr);	
	}
)RW");

std::string array[] ={
	"grass", "stone"
};

int main(int argc, char** argv){
	SDL_Window* window;
	SDL_Event ev;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
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
	std::map<std::string, core::Texture> m;
	core::Texture tex, tex1;
	GLfloat vertices[] ={
		-1.0, -1.0, 0.0, 0.0, 0.0,
		1.0, -1.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 0.0, 1.0, 0.0
	};

	int index = 0;

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	vbo = ctx->genBuffer(ctx);
	vao = ctx->genVertexArray(ctx);

	vs = ctx->createShader(ctx, ShaderType::VERTEX);
	fs = ctx->createShader(ctx, ShaderType::FRAGMENT);
	tex = ctx->createTexture(ctx);
	tex1 = ctx->createTexture(ctx);

	vs->source(1, vert, 0);
	fs->source(1, frag, 0);
	vs->compile();
	fs->compile();
	
	sp = ctx->createProgram(ctx, *vs, *fs);
	sp->link();
	d = ctx->createUniform("tex", sp); 

	std::cout << fs->get_log() << std::endl;
	std::cout << vs->get_log() << std::endl;

	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();

	vbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(vertices), vertices, BufferUsage::STATIC_DRAW );
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*5, (const void*)0);
	vao->attribPointer(1, 2, GL_FLOAT, false, sizeof(float)*5, (const void*)(sizeof(float)*3));
	vao->enableAttribute(1);
	vao->enableAttribute(0);

	vbo->unbind(BufferTypes::ARRAY_BUFFER);
	vao->unbind();

	ImageSurface surf("grass.png");
	Bitmap bm(surf.surf->pixels, surf.surf->w, surf.surf->h, PixelFormat::RGBA);
	ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_T , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_S , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	ctx->texImage2D(TextureTarget::TEXTURE2D, 0, bm.get_format(), bm.get_width(), bm.get_height(), 0, bm.get_format(), GL_UNSIGNED_BYTE, bm.get_data());	
	ctx->genMipmaps( TextureTarget::TEXTURE2D );

	ImageSurface s ("stone.png");
	bm = Bitmap(s.surf->pixels, s.surf->w, s.surf->h, PixelFormat::RGBA);
	ctx->bindTexture(TextureTarget::TEXTURE2D, *tex1);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_T , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_S , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	ctx->texImage2D(TextureTarget::TEXTURE2D, 0, bm.get_format(), bm.get_width(), bm.get_height(), 0, bm.get_format(), GL_UNSIGNED_BYTE, bm.get_data());	
	ctx->genMipmaps( TextureTarget::TEXTURE2D );
	
	m.insert(std::pair< std::string, core::Texture > (array[1], tex1));
	m.insert(std::pair< std::string, core::Texture > (array[0], tex));	
	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
			if(ev.type == SDL_KEYDOWN){
				index = 1;
			}
			else{
				index = 0;
			}
		}
		sp->use();
		ctx->setLineWidth(80);
		ctx->clearColor(0.5, 0.2, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, 1024, 768);

		d->uniformf(0);
		ctx->bindTexture(TextureTarget::TEXTURE2D, *m[array[index]]);
		glActiveTexture(GL_TEXTURE0);
		ctx->bindVertexArray(*vao);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);
		ctx->unbindVertexArray();


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
