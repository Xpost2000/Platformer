#ifndef TEXTURE_H
#define TEXTURE_H
#include "IObjectHandle.h"
#include "TextureParameter.h"
#include "Comparable.h"
#include "IDevice.h"
#include <memory>
class Bitmap;
class IDevice;
class Texture : public IObjectHandle, public Comparable<Texture> {
	public:
	Texture();
	Texture(const std::shared_ptr<IDevice>& dev);
	Texture(const Texture& other) = default;
	~Texture();
	const HandleType is_type() const{ return HandleType::HANDLE_TEXTURE; }
	void bindTexture(TextureTarget);
	void unbindTexture(TextureTarget);
	// targ, bitmap, level, border, type, data
	void texImage2D(TextureTarget, Bitmap&, GLint, GLint, GLenum);
	void texImage2D(TextureTarget, GLint, GLint, GLsizei, GLsizei, GLint border, GLenum, GLenum, const GLvoid*);
	void textureParameter(TextureTarget, TextureParameter, ParamValue);
	
	bool operator > ( Texture rhs ) { return true;}
	bool operator < ( Texture rhs ) { return true;}
	bool operator >= ( Texture rhs ) { return true;}
	bool operator <= ( Texture rhs ) { return true; }
	bool operator == ( Texture rhs ) { return (obj == rhs.obj);}
	private:
	std::shared_ptr<IDevice> device = nullptr;
};

#endif
