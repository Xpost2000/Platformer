#include <iostream>
#include <map>
#include <SDL2/SDL_image.h>
#include "mat4.hpp"
#include "BitmapUtil.h"
#include "typedefs.h"
#include "TestShader.h"
#include "DefaultShader.h"
#include "SpriteBatcher.h"
#include "PostProcessorShader.h"
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
	std::map<std::string, ptrs::Texture> m;
	ptrs::Texture tex, tex1;
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
	
	SpriteBatcher sb(ctx);
	DefaultShader ds(ctx);
	PostProcessorShader ps(ctx);
	glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4();
	ds.setMatrices(proj, view);
	while(true){
		while(SDL_PollEvent(&ev)){
			if(ev.type== SDL_QUIT){
				return 0;
			}
			if(ev.type == SDL_KEYDOWN){
			}
			else{
			}
		}
		ctx->bindFramebuffer( FrameBufferTarget::FRAMEBUFFER, *fbo );
		ctx->clearColor(0.5, 0.2, 0.3);
		ctx->clear(BufferClear::COLOR_DEPTH_BUFFERS);
		ctx->viewport(0, 0, WIDTH, HEIGHT);
		ds.use();
	
		ctx->bindTexture(TextureTarget::TEXTURE2D, *tex);
		sb.draw(Vec2(200, 150), Vec4(0, 0, 1, 1), Vec2(500, 300), Vec3(1));
		sb.render();

		ds.unuse();
		ctx->unbindFramebuffer(FrameBufferTarget::FRAMEBUFFER);


	
		ps.use();
		ctx->bindTexture(TextureTarget::TEXTURE2D, *pp);
		scrVao->bind();
		ctx->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
		scrVao->unbind();
		ctx->unbindTexture(TextureTarget::TEXTURE2D);
		ps.unuse();	


		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}
