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

class RandomNumberInt{
	public:
		RandomNumberInt(int max, int min) : max(max), min(min){
		}
		int getNumber(){
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> roll(min, max);
			return roll(gen);
		}
	private:
		int max, min;
		
};

class RandomNumberFloat{
	public:
		RandomNumberFloat(float max, float min) : max(max), min(min){
		}
		float getNumber(){
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> roll(min, max);
			return roll(gen);
		}
	private:
		float max, min;
};
#endif
