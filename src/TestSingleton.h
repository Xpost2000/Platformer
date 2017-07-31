#ifndef TEST_SINGLETON
#define TEST_SINGLETON
#include "Singleton.h"
#include <iostream>

class Test : public Singleton<Test> {
	public:
		~Test() { std::cout << "Singleton::dtor" << std::endl; }
		void printA() { std::cout << "A\n";}
		template<typename T = int>
		T square( const T num) { return num*num;}
};

#endif
