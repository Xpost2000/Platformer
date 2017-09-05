#include "Coin.h"

Coin::Coin(Vec2 pos, Vec2 size)
: Entity(pos, size, Vec2(0), Vec4(1)){
	magic = COIN;
}

const int Coin::get_value(){
	// I do very simple math for results
	int result = size.x() * size.y();
	result *= 5;
	return (result / 2)-(int)size.x()%3;
}

Vec4& Coin::getColor(){
    const int sum = (int)size.x() + (int)size.y() ;
    if(sum <= 30){
	   color = Vec4(184, 115, 51, 255).rgb8_normalize();
    }else if( sum > 30 && sum < 60 ){
	   color = Vec4(192, 192, 192, 255).rgb8_normalize();
    }else if( sum > 60 ){
	   color = Vec4(255, 215, 0, 255).rgb8_normalize();
    }
    color.a() = 1;
    return color;
}
