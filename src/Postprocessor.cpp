#include "Postprocessor.h"

PostProcessor::PostProcessor( const std::shared_ptr<IDevice>& dev, int w, int h): device(dev){
	fbo = new Framebuffer(device);
	rbo = new Renderbuffer(device);
	vbo = new Buffer(device);
	vao = new VertexArray(device);
	out = new Texture(device);
	shader = new PostProcessorShader(device);

	device->bindFramebuffer( FrameBufferTarget::FRAMEBUFFER, *fbo );
	device->bindRenderbuffer( *rbo );
	device->bindTexture( TextureTarget::TEXTURE2D, *out );
	device->textureParameter( TextureTarget::TEXTURE2D, TextureParameter::MAG_FILTER, ParamValue::LINEAR );
	device->textureParameter( TextureTarget::TEXTURE2D, TextureParameter::MIN_FILTER, ParamValue::LINEAR );
	out->texImage2D(TextureTarget::TEXTURE2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	device->frameBufferTexture(FrameBufferTarget::FRAMEBUFFER, FrameBufferAttachment::COLOR_ATTACHMENT0, TextureTarget::TEXTURE2D, *out, 0);
	device->unbindTexture( TextureTarget::TEXTURE2D );
	device->renderBufferStorage( RenderBufferInternalFormat::DEFAULT, w, h );
	device->frameBufferRenderbuffer( FrameBufferAttachment::DEPTH_STENCIL_ATTACHMENT, *rbo );
	// more exposed GL calls.
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glBindRenderbuffer( GL_RENDERBUFFER, 0);

	GLfloat screen[] = {
		-1.0, 1.0, 0.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 0.0, 0.0,
		 1.0, 1.0, 0.0, 1.0, 1.0,
		 1.0, -1.0, 0.0, 1.0, 0.0
	};

	vbo->bind(BufferTypes::ARRAY_BUFFER);
	vao->bind();
	vbo->bufferData( BufferTypes::ARRAY_BUFFER, sizeof(screen), screen, BufferUsage::STATIC_DRAW );
	vao->attribPointer(0, 3, GL_FLOAT, false, sizeof(float)*5, (const void*)0);
	vao->attribPointer(1, 2, GL_FLOAT, false, sizeof(float)*5, (const void*)(sizeof(float)*3));
	vao->enableAttribute(1);
	vao->enableAttribute(0);
	vao->unbind();
	vbo->unbind(BufferTypes::ARRAY_BUFFER);
}
PostProcessor::~PostProcessor(){
	delete shader;
	delete out;
	delete vbo;
	delete vao;
	delete fbo;
	delete rbo;
}

void PostProcessor::begin(){
	device->bindFramebuffer( FrameBufferTarget::FRAMEBUFFER , *fbo);
	device->clear(BufferClear::COLOR_DEPTH_BUFFERS);
}
void PostProcessor::end(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	shader->use();
	device->bindTexture(TextureTarget::TEXTURE2D, *out);
	vao->bind();
	device->drawArrays(DrawMode::TRIANGLE_STRIPS, 0, 4);
	vao->unbind();
	device->unbindTexture(TextureTarget::TEXTURE2D);
	shader->unuse();
}
