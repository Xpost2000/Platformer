#ifndef RNG_H
#define RNG_H
/*
 * Useful convience class.
 * it just uses the built in mt19937 and random_distrub
 * functions and classes featured in C++11.
 */
#include <time.h>
#include <random>
#include <functional>

class RandomInt{
	public:
	RandomInt( int min, int max ) : rng(std::random_device()()), dis(min, max) {
	}
	int get(){
		return dis(rng);
	}
	int operator()(){	
		return get();
	}
	private:
	std::mt19937 rng;
	std::uniform_int_distribution<int> dis;
};
class RandomFloat{
	public:
	RandomFloat ( float min , float max ) : rng(std::random_device()()), dis(min, max) {
	}
	float get(){
		return dis(rng);
	}
	float operator()(){
		return get();
	}
	private:
	std::mt19937 rng;
	std::uniform_real_distribution<float> dis;
};

#endif
