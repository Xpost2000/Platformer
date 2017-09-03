#ifndef FREETYPE_TEXT_H
#define FREETYPE_TEXT_H
#include "IDevice.h"
#include "IShaderSet.h"
#include <memory>
#include <vector>
#include <map>
#include "ShaderUniform.h"
#include "vector_typedef.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "matrix_typedef.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
/*
 * TextRenderer.
 * Now because I'm starting to forget even my own code I'll have to start
 * breaking my previous conventions. I'll refactor all of this because
 * I'm going to at least get this to a working point.
 *
 * I finally caught a factor in my bitmap rendering failing but I didn't make many commits
 * earlier so I couldn't go to the point where it was sort of working
 *
 * I'll refactor for Linux later.
 */
struct Character{
	GLuint texture;
	glm::ivec2 bearing;
	glm::ivec2 size;
	int advance;
};
class TextRendererShader : public IShaderSet{
	public:
		TextRendererShader( const std::shared_ptr<IDevice>& dev ){
			vs = new Shader(dev, ShaderType::VERTEX);
			fs = new Shader(dev, ShaderType::FRAGMENT);
			std::string vert(R"RW(
				#version 330 core
				layout(location=0) in vec2 position;
				layout(location=1) in vec2 uv;
				uniform mat4 proj;
				uniform mat4 view;
				uniform bool transform=false;
				out vec2 texCoords;
				void main(){
				//	if(transform){
				//		gl_Position = proj*view*vec4(position.xy, 0, 1);
				//	}else{
						gl_Position = proj*vec4(position.xy, 0, 1);
						texCoords = uv;
				//	}
				}
			)RW");
			std::string frag(R"RW(
				#version 330 core
				in vec2 texCoords;
				uniform vec3 clr;
				uniform sampler2D tex;
				out vec4 color;
				void main(){
					vec4 sampled = vec4(1, 1, 1, texture(tex, texCoords).r);
					color =  sampled;
				}
			)RW");
			vs->source(1, vert, 0);
			fs->source(1, frag, 0);
			vs->compile();
			fs->compile();
			sp = new ShaderProgram(dev, *vs, *fs);
			sp->link();

			proj = new ShaderUniform( "proj", *sp );
			view = new ShaderUniform( "view", *sp );
			transform = new ShaderUniform( "transform", *sp );
			tex = new ShaderUniform( "tex", *sp );
			clr = new ShaderUniform( "clr", *sp );
		}
		~TextRendererShader(){
			delete tex;
			delete clr;
			delete transform;
			delete view;
			delete proj;
			delete vs;
			delete fs;
			delete sp;
		}
		void setMatrices( glm::mat4 p, glm::mat4 v ){
			view->uniformMatrix4(1, false, glm::value_ptr(v));
			proj->uniformMatrix4(1, false, glm::value_ptr(p));
		}
		void setTransform( bool val ){
			transform->uniformi(val);
		}
		void setTex( int val ){
			tex->uniformi(val);
		}
		void setColor( Vec3 clr ){
			this->clr->uniformf( clr.x(), clr.y(), clr.z() );
		}
	private:
		//vert
		ShaderUniform* proj=nullptr;
		ShaderUniform* view=nullptr;
		ShaderUniform* transform=nullptr;
		//frag
		ShaderUniform* tex=nullptr;
		ShaderUniform* clr=nullptr;
};
class TextRenderer{
	public:
		TextRenderer( const std::shared_ptr<IDevice>& dev, std::string font_path ){
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData( GL_ARRAY_BUFFER, sizeof(float)*6*4, (void*)0, GL_DYNAMIC_DRAW );
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)(sizeof(float)*2));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			shader = new TextRendererShader(dev);
			FT_Init_FreeType(&ftI);

			FT_New_Face(ftI, font_path.c_str(), 0, &font);
			FT_Set_Pixel_Sizes( font, 0,  20);
			glPixelStorei( GL_UNPACK_ALIGNMENT,  1 );
			for( unsigned char c = 0; c < 128; ++c ){
				GLuint tex;
				FT_Load_Char( font , c, FT_LOAD_RENDER );
				glGenTextures(1, &tex);
				glBindTexture( GL_TEXTURE_2D, tex );
				glTexImage2D(
						GL_TEXTURE_2D,
						0,
						GL_RED,
						font->glyph->bitmap.width,
						font->glyph->bitmap.rows,
						0,
						GL_RED,
						GL_UNSIGNED_BYTE,
						font->glyph->bitmap.buffer);
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
				glBindTexture(GL_TEXTURE_2D, 0);
				Character temp = {
					tex,
					glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
					glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
					font->glyph->advance.x
				};
				characters.insert(std::pair<char, Character>( c, temp ));
			}
		}
		~TextRenderer(){
			delete shader;
			FT_Done_Face(font);
			FT_Done_FreeType(ftI);
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
		}
		void render( std::string txt, glm::vec2 pos, float scale, glm::vec3 color ){
			shader->use();
			shader->setTex(0);
			shader->setColor( Vec3(color.x, color.y, color.z) );
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			std::string::const_iterator c;
			for (c = txt.begin(); c != txt.end(); c++){
				Character ch = characters[*c];
				float x = pos.x + ch.bearing.x * scale;
				float y = pos.y + (characters['H'].bearing.y - ch.bearing.y) * scale;
				float w = ch.size.x * scale;
				float h = ch.size.y * scale;
				float verts[6][4] = {
					// tri 1
					{x, y+h, 0, 1},
					{x + w, y, 1, 0},
					{x, y, 0, 0},
					// tri 2
					{x, y +h, 0, 1},
					{x+w, y+h, 1, 1},
					{x+w, y, 1, 0}
				};
				glBindTexture(GL_TEXTURE_2D, ch.texture);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				pos.x += (ch.advance >> 6) * scale;
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
		void setMatrices( glm::mat4 p, glm::mat4 v ){
			shader->setMatrices(p, v);
		}
	private:
		GLuint vbo, vao;
		FT_Library ftI;
		FT_Face font;
		TextRendererShader* shader;
		std::map<GLchar, Character> characters;
};

#endif
