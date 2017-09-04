#include "BitmapTextRenderer.h"

// I wrote a program to generate the uv tables from a map file generated from the sprite packing program I use.
static Vec4 uv_table[]={
Vec4( 0 , 0 , 0.125 , 0.125),
Vec4( 0.166667 , 0 , 0.125 , 0.125),
Vec4( 0.333333 , 0 , 0.125 , 0.125),
Vec4( 0 , 0.166667 , 0.125 , 0.125),
Vec4( 0.166667 , 0.166667 , 0.125 , 0.125),
Vec4( 0 , 0.333333 , 0.125 , 0.125),
Vec4( 0.166667 , 0.333333 , 0.125 , 0.125),
Vec4( 0.333333 , 0.166667 , 0.125 , 0.125),
Vec4( 0.333333 , 0.333333 , 0.125 , 0.125),
Vec4( 0.5 , 0 , 0.125 , 0.125),
Vec4( 0.5 , 0.166667 , 0.125 , 0.125),
Vec4( 0.666667 , 0 , 0.125 , 0.125),
Vec4( 0.5 , 0.333333 , 0.125 , 0.125),
Vec4( 0.666667 , 0.166667 , 0.125 , 0.125),
Vec4( 0.833333 , 0 , 0.125 , 0.125),
Vec4( 0.833333 , 0.166667 , 0.125 , 0.125),
Vec4( 0.666667 , 0.333333 , 0.125 , 0.125),
Vec4( 0.833333 , 0.333333 , 0.125 , 0.125),
Vec4( 0 , 0.5 , 0.125 , 0.125),
Vec4( 0.166667 , 0.5 , 0.125 , 0.125),
Vec4( 0 , 0.666667 , 0.125 , 0.125),
Vec4( 0.333333 , 0.5 , 0.125 , 0.125),
Vec4( 0.166667 , 0.666667 , 0.125 , 0.125),
Vec4( 0 , 0.833333 , 0.125 , 0.125),
Vec4( 0.166667 , 0.833333 , 0.125 , 0.125),
Vec4( 0.5 , 0.5 , 0.125 , 0.125),
Vec4( 0.333333 , 0.666667 , 0.125 , 0.125),
Vec4( 0.666667 , 0.5 , 0.125 , 0.125),
Vec4( 0.5 , 0.666667 , 0.125 , 0.125),
Vec4( 0.333333 , 0.833333 , 0.125 , 0.125),
Vec4( 0.666667 , 0.666667 , 0.125 , 0.125),
Vec4( 0.5 , 0.833333 , 0.125 , 0.125),
Vec4( 0.833333 , 0.5 , 0.125 , 0.125)
};

// I carefully reconsider how to calculate the uvs.
// I'm seriously starting to consider hand calculating them because I cannot find the correct equation
// or it would require a serious rewrite some where.

BitmapTextRenderer::BitmapTextRenderer( const std::shared_ptr<IDevice>& dev )
: device(dev){
	textShader = std::make_shared<TextShader>( device );
	batch = new SpriteBatcher( device );
}

BitmapTextRenderer::~BitmapTextRenderer(){
	delete batch;
}

void BitmapTextRenderer::render( const char* text, Vec2 pos, float size , Vec4 color, Texture& tex, bool static_text ){
	textShader->use();
	tex.bindTexture(TextureTarget::TEXTURE2D);
	textShader->setTex(0);
	textShader->viewMatrixActive( !static_text );
	int i = 0;
	int offset=0;
	while(*text != '\0'){
		if(*text == '\n') { offset+=size; }
		batch->draw(Vec2(pos.x()+i*size, pos.y()+offset), uv_calc(*text), Vec2(size), color);
		text++;
		i++;
	}
//	batch->draw(pos, uv_calc(0), Vec2(size), color);
	batch->render();
}

/*
 * TODO: Fix this. But for now going to swap to free type because rn it's the easiest option since I'm having issues with the UVs.
 */
Vec4 BitmapTextRenderer::uv_calc( int index ){
	switch(index){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			// I'm sort of 'atoi'-ing the situation
			return uv_table[index-'0'];
			break;
		case ':':
			return uv_table[10];
			break;
		default:
			break;
	};
}
