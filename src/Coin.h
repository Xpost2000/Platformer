#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity{
	public:
		Coin(){}
		Coin(const Coin& other)= default;
		Coin(Vec2 pos, Vec2 size);
		const int get_value();	
		Vec4& getColor();
	private:
};

#endif
