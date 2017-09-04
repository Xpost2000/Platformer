#ifndef TEXT_RENDERER_BITMAP_H
#define TEXT_RENDERER_BITMAP_H
#include <memory>
#include "Texture.h"
#include "SpriteBatcher.h"
#include "TextShader.h"
class BitmapTextRenderer{
	public:
		BitmapTextRenderer( const std::shared_ptr<IDevice>& dev );
		~BitmapTextRenderer();
		void setMatrices( glm::mat4 proj, glm::mat4 view ){ textShader->use(); textShader->SetMatrices(proj, view); }
		void render( const char* text, Vec2 pos, float size, Vec4 color, Texture& tex, bool static_text=false );
	private:
		Vec4 uv_calc( int index );
		std::shared_ptr<IDevice> device=nullptr;
		std::shared_ptr<TextShader> textShader=nullptr;
		SpriteBatcher* batch=nullptr;
};
#endif
