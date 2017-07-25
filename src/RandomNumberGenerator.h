#ifndef RNG_H
#define RNG_H
/*
 * Useful convience class.
 * it just uses the built in mt19937 and random_distrub
 * functions and classes featured in C++11.
 * for windows use the boost implementation.
 *
 * Thanks to boost I spend virtually no effort in the code base.
 */
#include <time.h>
#ifdef __linux__ // The C++11 random library works on linux. Or so I'm told. I'll test it myself later.
#include <random> // Include the C++11 random library
#endif 
#ifdef __WIN32__ // My windows compiler atm is TDM GCC 5.1.0, which works on my windows machine.
// Include Boost random library on Windows.
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#endif
#ifdef __WIN32__
class RandomInt{
	public:
	RandomInt(int min, int max) : rng(boost::random::random_device()()), dis(min, max){
	}
	int get(){
		return dis(rng);
	}
	int operator()(){	
		return get();
	}
	private:
	boost::random::mt19937 rng;
	boost::random::uniform_int_distribution<int> dis;
};
#endif

#ifdef __linux__
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
#endif
#include <iostream>
#ifdef __WIN32__
class RandomFloat{
	public:
	RandomFloat( float min, float max ) : rng(boost::random::random_device()()), dis(min, max) {
	}
	float get(){
		return dis(rng);
	}
	float operator()(){
		return get();
	}
	private:
	boost::random::mt19937 rng;
	boost::random::uniform_real_distribution<float> dis;
};
#endif  

#ifdef __linux__
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

#endif
