#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity{
	public:
		Coin(){}
		Coin(const Coin& other)= default;
		const int get_value();	
	private:
};

#endif
