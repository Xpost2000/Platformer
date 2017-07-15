#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"

std::string vert ( R"RW(
	#version 330 core
	layout(location=0) in vec3 pos;
	layout(location=1) in vec2 clr;
	layout(location=2) in vec3 fst;
	out vec2 vClr;
	out vec3 vFst;
	uniform mat4 model;
	void main(){
		gl_Position = model*vec4(pos, 1.0f);
		vClr = clr;
		vFst = fst;
	}
)RW");
std::string frag(R"RW(
	#version 330 core
	uniform sampler2D tex;
	in vec2 vClr;
	in vec3 vFst;
	out vec4 color;
	uniform float d;
	void main(){
		color = texture(tex, vClr);	
		color *= vec4(d);
		color += vec4(vFst, 1.0f);
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
	ptrs::IDevice ctx = std::make_shared<GLDevice>(window, info);
	ptrs::Buffer vbo;
	ptrs::Buffer vbo3;
	ptrs::VertexArray vao3;
	ptrs::Buffer vbo2;
	ptrs::VertexArray vao2;
	ptrs::VertexArray vao;
	ptrs::Shader vs, fs;
	ptrs::ShaderProgram sp;
	ptrs::ShaderUniform d;
	ptrs::ShaderUniform rlD;
	ptrs::ShaderUniform matrix;
	std::map<std::string, ptrs::Texture> m;
	ptrs::Texture tex, tex1;
	GLfloat vertices[] ={
		-.5, -.5, 0.0, 0.0, 0.0, 0.2, 0.0, 0.0,
		.5, -.5, 0.0, 1.0, 1.0, 0.0, 0.0, 0.2,
		0., .5, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0
	};
	GLfloat rect[] = {
		-1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0,
		-1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		1.0, 0.0, 0.0, 1, 1, 1.0, 1.0, 1.0,
		1.0, -1.0, 0.0,  1.0, 0.0, 0.0, 0.0, 0.0
	};
	GLfloat gradient[] = {
		-1.0, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 1.0, 1.0, 1.0,
		 1.0, 1.0, 0.0, 0.0, 0.0, 1.0,
		 1.0, -1.0, 0.0, 1.0, 1.0, 1.0
	};

	int index = 0;

	std::cout << "According to the OpenGL context \n";

	std::cout << "MAJOR : " << ctx->getInteger(GetParam::MAJOR_VERSION) << std::endl;
	std::cout << "MINOR : " << ctx->getInteger(GetParam::MINOR_VERSION) << std::endl;
	
	vbo = ctx->genBuffer(ctx);
	vao = ctx->genVertexArray(ctx);

	vbo2 = ctx->genBuffer(ctx);
	vao2 = ctx->genVertexArray(ctx);
	
	vbo3 = ctx->genBuffer(ctx);
	vao3 = ctx->genVertexArray(ctx);

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
	matrix = ctx->createUniform("model", sp);
	rlD = ctx->createUniform("d", sp);

	std::cout << fs->get_log() << std::endl;
	std::cout << vs->get_log() << std::endl;

	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();

	vbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(vertices), vertices, BufferUsage::STATIC_DRAW );
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*8, (const void*)0);
	vao->attribPointer(1, 2, GL_FLOAT, false, sizeof(float)*8, (const void*)(sizeof(float)*3));
	vao->attribPointer(2, 3, GL_FLOAT, false, sizeof(float)*8, (const void*)(sizeof(float)*5));
	vao->enableAttribute(2);
	vao->enableAttribute(1);
	vao->enableAttribute(0);

	vbo->unbind(BufferTypes::ARRAY_BUFFER);
	vao->unbind();

	vbo2->bind(BufferTypes::ARRAY_BUFFER);
	vao2->bind();
	vbo2->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(rect), rect, BufferUsage::STATIC_DRAW );
	vao2->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*8, (const void*)0);
	vao2->attribPointer(1, 2, GL_FLOAT, false, sizeof(float)*8, (const void*)(sizeof(float)*3));
	vao2->attribPointer(2, 3, GL_FLOAT, false, sizeof(float)*8, (const void*)(sizeof(float)*5));
	vao2->enableAttribute(2);
	vao2->enableAttribute(1);
	vao2->enableAttribute(0);
	vao2->unbind();
	vbo2->unbind(BufferTypes::ARRAY_BUFFER);


	vbo3->bind(BufferTypes::ARRAY_BUFFER);
	vao3->bind();
	vbo3->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(gradient), gradient, BufferUsage::STATIC_DRAW );
	vao3->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*6, (const void*)0);
	vao3->attribPointer(2, 3, GL_FLOAT, false, sizeof(float)*6, (const void*)(sizeof(float)*3));
	vao3->enableAttribute(2);
	vao3->enableAttribute(0);
	vao3->unbind();
	vbo3->unbind(BufferTypes::ARRAY_BUFFER);

	// using delegated constructor
	ImageSurface es("grass.png");
	ImageSurface s ("stone.png");
	Bitmap bm (es.surf, PixelFormat::RGBA);
	ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_T , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_S , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	tex->texImage2D(TextureTarget::TEXTURE2D, bm, 0, 0, GL_UNSIGNED_BYTE);	
	ctx->genMipmaps( TextureTarget::TEXTURE2D );

	bm = Bitmap(s.surf, PixelFormat::RGBA);
	ctx->bindTexture(TextureTarget::TEXTURE2D, *tex1);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_T , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::WRAP_S , ParamValue::REPEAT);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	tex1->texImage2D(TextureTarget::TEXTURE2D, bm, 0, 0, GL_UNSIGNED_BYTE);	
	ctx->genMipmaps( TextureTarget::TEXTURE2D );
	
	m.insert(std::pair< std::string, ptrs::Texture > (array[1], tex1));
	m.insert(std::pair< std::string, ptrs::Texture > (array[0], tex));	
	ctx->unbindTexture( TextureTarget::TEXTURE2D );
	Matrix4f model;
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

		model = Matrix4f::Identity();
		matrix->uniformMatrix4(1, false, model.data());
		ctx->bindVertexArray(*vao3);
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
		
		ctx->bindVertexArray(*vao);
		d->uniformi(0);
		
		ctx->bindTexture(TextureTarget::TEXTURE2D, *m[array[index]]);
		model = Matrix4f::Identity();
		model = Matrix4f::translate( model, Vec3( 0.5, 0.0, 0.0 ) );
		model = Matrix4f::rotate( model, 0.0f, Vec3( 0.0, 0.0, 1.0 ) );
		matrix->uniformMatrix4(1, false, model.data());
		rlD->uniformf(0.25);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		model = Matrix4f::Identity();
		model = Matrix4f::translate( model, Vec3( -0.5, 0.0, 0.0 ) );
		model = Matrix4f::rotate( model, 0.0f, Vec3( 0.0, 0.0, 1.0 ) );
		matrix->uniformMatrix4(1, false, model.data());
		rlD->uniformf(0.5);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);
		
		model = Matrix4f::Identity();
		matrix->uniformMatrix4(1, false, model.data());	
		rlD->uniformf(0.7f);
		glActiveTexture(GL_TEXTURE0);
		ctx->bindVertexArray(*vao);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		model = Matrix4f::Identity();
		model = Matrix4f::translate(model, Vec3(0, -0.5, 0.0));
		model = Matrix4f::scale( model, Vec3(2.67, 0.7, 1.0) );
		matrix->uniformMatrix4(1, false, model.data());	
		rlD->uniformf(0.8f);
		glActiveTexture(GL_TEXTURE0);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		vao2->bind();
		model = Matrix4f::Identity();
		model = Matrix4f::translate(model, Vec3(0, -.5, 0.0));
		model = Matrix4f::scale(model, Vec3(1.0, 0.5, 1.0));
		rlD->uniformf(1);
		matrix->uniformMatrix4(1, false, model.data());	
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);

		ctx->unbindVertexArray();
		ctx->unbindTexture(TextureTarget::TEXTURE2D);


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
