#include "Coin.h"

const int Coin::get_value(){
	// I do very simple math for results
	int result = size.x() * size.y();
	result *= 5;
	return (result / 2)-(int)size.x()%3;
}
