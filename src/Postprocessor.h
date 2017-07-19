#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H
#include "PostProcessorShader.h"
#include "Framebuffer.h"
#include "Buffer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Renderbuffer.h"
#include "IDevice.h"
class PostProcessor{
	public:
		PostProcessor( const std::shared_ptr<IDevice>& dev,int w, int h );
		~PostProcessor();
		void begin();
		void end();
	private:
		std::shared_ptr<IDevice> device = nullptr;
		PostProcessorShader* shader = nullptr;
		Texture* out=nullptr;
		Buffer* vbo=nullptr;
		VertexArray* vao=nullptr;
		Framebuffer* fbo=nullptr;
		Renderbuffer* rbo=nullptr;
};

#endif
