#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"

std::string vert1 ( R"RW(
	#version 330 core
	layout(location=0) in vec3 pos;
	layout(location=1) in vec2 clr;
	out vec2 vClr;
	void main(){
		gl_Position = vec4(pos, 1.0f);
		vClr = clr;
	}
)RW");
std::string frag1(R"RW(
	#version 330 core
	uniform sampler2D tex;
	in vec2 vClr;
	out vec4 color;
	void main(){
		color = texture(tex, vClr);	
		color -= vec4(0.0, 0.4, 1., 1.0);
	}
)RW");
std::string array[] ={
	"grass", "stone"
};

#define WIDTH 1280
#define HEIGHT 720
int main(int argc, char** argv){
	SDL_Window* window;
	SDL_Event ev;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Test Letter X OGL Wrapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
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
	GLfloat screen[] = {
		-1.0, 1.0, 0.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 0.0, 0.0,
		 1.0, 1.0, 0.0, 1.0, 1.0,
		 1.0, -1.0, 0.0, 1.0, 0.0
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

	tex = ctx->createTexture(ctx);
	tex1 = ctx->createTexture(ctx);

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

	ptrs::Shader pVs = ctx->createShader(ctx, ShaderType::VERTEX), pFs = ctx->createShader(ctx, ShaderType::FRAGMENT);
	ptrs::Texture pp = ctx->createTexture(ctx);
	ptrs::Framebuffer fbo = ctx->createFramebuffer(ctx);
	ptrs::Renderbuffer rbo = ctx->createRenderbuffer(ctx);
	ptrs::Buffer scrVbo = ctx->genBuffer(ctx);
	ptrs::VertexArray scrVao = ctx->genVertexArray(ctx);

	ctx->bindFramebuffer( FrameBufferTarget::FRAMEBUFFER , *fbo );
	ctx->bindRenderbuffer( *rbo );
	ctx->bindTexture(TextureTarget::TEXTURE2D, *pp);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MAG_FILTER , ParamValue::LINEAR);
	ctx->textureParameter(TextureTarget::TEXTURE2D , TextureParameter::MIN_FILTER , ParamValue::LINEAR);
	pp->texImage2D(TextureTarget::TEXTURE2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);	
	ctx->frameBufferTexture(FrameBufferTarget::FRAMEBUFFER, FrameBufferAttachment::COLOR_ATTACHMENT0, TextureTarget::TEXTURE2D, *pp, 0);
	ctx->unbindTexture(TextureTarget::TEXTURE2D);
	ctx->renderBufferStorage( RenderBufferInternalFormat::DEFAULT, WIDTH, HEIGHT );
	ctx->frameBufferRenderbuffer( FrameBufferAttachment::DEPTH_STENCIL_ATTACHMENT , *rbo );


	scrVbo->bind(BufferTypes::ARRAY_BUFFER);
	scrVao->bind();
	scrVbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(screen), screen, BufferUsage::STATIC_DRAW );
	scrVao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*5, (const void*)0);
	scrVao->attribPointer(1, 2, GL_FLOAT, false, sizeof(float)*5, (const void*)(sizeof(float)*3));
	scrVao->enableAttribute(1);
	scrVao->enableAttribute(0);
	scrVao->unbind();
	scrVbo->unbind(BufferTypes::ARRAY_BUFFER);

	pVs->source(1, vert1, 0);
	pFs->source(1, frag1, 0);
	pVs->compile();
	pFs->compile();
	
	ptrs::ShaderProgram pSp = ctx->createProgram(ctx, *pVs, *pFs);
	pSp->link();
	TestShader t(ctx);
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
		ctx->bindFramebuffer( FrameBufferTarget::FRAMEBUFFER, *fbo );
		t.use();
		ctx->setLineWidth(80);
		ctx->clearColor(0.5, 0.2, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, WIDTH, HEIGHT);

		model = Matrix4f::Identity();
		t.setMatrix(model);
		ctx->bindVertexArray(*vao3);
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
		
		ctx->bindVertexArray(*vao);
		t.setTex(0);
		
		ctx->bindTexture(TextureTarget::TEXTURE2D, *m[array[index]]);
		model = Matrix4f::Identity();
		model = Matrix4f::translate( model, Vec3( 0.5, 0.0, 0.0 ) );
		model = Matrix4f::rotate( model, 0.0f, Vec3( 0.0, 0.0, 1.0 ) );
		t.setMatrix(model);
		t.setD(0.25);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		model = Matrix4f::Identity();
		model = Matrix4f::translate( model, Vec3( -0.5, 0.0, 0.0 ) );
		model = Matrix4f::rotate( model, 0.0f, Vec3( 0.0, 0.0, 1.0 ) );
		t.setMatrix(model);
		t.setD(0.5);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);
		
		model = Matrix4f::Identity();
		t.setMatrix(model);
		t.setD(0.7);
		glActiveTexture(GL_TEXTURE0);
		ctx->bindVertexArray(*vao);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		model = Matrix4f::Identity();
		model = Matrix4f::translate(model, Vec3(0, -0.5, 0.0));
		model = Matrix4f::scale( model, Vec3(2.67, 0.7, 1.0) );
		t.setMatrix(model);
		t.setD(0.8);
		glActiveTexture(GL_TEXTURE0);
		ctx->drawArrays(DrawMode::TRIANGLES, 0, 3);

		vao2->bind();
		model = Matrix4f::Identity();
		model = Matrix4f::translate(model, Vec3(0, -.5, 0.0));
		model = Matrix4f::scale(model, Vec3(1.0, 0.5, 1.0));
		t.setD(1);
		t.setMatrix(model);
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
		t.unuse();
		ctx->unbindVertexArray();
		ctx->unbindTexture(TextureTarget::TEXTURE2D);
		ctx->unbindFramebuffer(FrameBufferTarget::FRAMEBUFFER);


	
		pSp->use();
		ctx->bindTexture(TextureTarget::TEXTURE2D, *pp);
		scrVao->bind();
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
		scrVao->unbind();
		ctx->unbindTexture(TextureTarget::TEXTURE2D);
		


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
