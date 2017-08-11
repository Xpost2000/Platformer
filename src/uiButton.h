#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "vector_typedef.h"
#include "vec2.hpp"
#include "Sound.h"
#include "vec3.hpp"
// this button is a ui element.
// specifically for the main menu right now.
enum class ButtonType{
	Start,
	Options,
	Quit,
	Credits
};
class uiButton{
	public:
		uiButton(const uiButton& other) = default;
		uiButton(){}
		uiButton( Vec2 pos, Vec2 size, Vec3 color, Vec3 highlightColor, ButtonType id ) : pos(pos), size(size), color(color), highlightColor(highlightColor), id(id){
		}
		void update( int x, int y ){
			if(mouse_inside(x, y)){
				color = highlightColor;
			}else{
				color = Vec3(1.0);	
			}
		}
		bool mouse_inside( int x, int y ){
			bool inside=true;
			if(x > pos.x() + size.x()){
				inside = false;
			}
			if(x < pos.x()){
				inside = false;
			}
			if(y > pos.y() + size.y()){
				inside = false;
			}
			if(y < pos.y()){
				inside = false;
			}
			if(inside&&!sound_played){
					Sound::play_sound("beep");
					sound_played=true;
			}else if(!inside){ sound_played=false; }
			return inside;
		}
		Vec2 getPos(){ return pos; }
		Vec2 getSize() { return size; }
		Vec3 getColor() { return color; }
		Vec4 getUvs(){
			switch(id){
				case ButtonType::Start:
					return Vec4(0, 248.0f/512.0f, 300.0f/512.0f, 308.0f/512.0f);
					break;
				case ButtonType::Options:
					return Vec4(0, 186.0f/512.0f, 300.0f/512.0f, 248.0f/512.0f);
					break;
				case ButtonType::Quit:
					return Vec4(0, 62.0f/512.0f, 300.0f/512.0f, 128.0f/512.0f);
					break;
				case ButtonType::Credits:
					return Vec4(0, 0, 300/512.0f, 60.0f/512.0f);
					break;
			}
		}
		ButtonType type() { return id; }
	private:
	bool sound_played=false;
	ButtonType id;
	Vec2 pos;		
	Vec2 size;
	Vec3 color;
	Vec3 highlightColor;
};
#endif
