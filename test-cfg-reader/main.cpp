/*
 * I'm going to make small test / demonstration programs to show
 * how I will do stuff that the folders are called.
 * */

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char** argv){
	if(argc < 1){
		return -1;
	}else{
		std::ifstream input(argv[1]);
		std::string garbage;	
		std::string token;
		std::string dir_assests;
		int resX=0;
		int resY=0;
		while( input >> token ){
			// comment found
			if(token == "##" || token == "#"){
				std::getline(input, garbage);	
			}else if(token == "resolution_x="){
				input >> resX;
			}else if(token == "resolution_y="){
				input >> resY;
			}else if(token == "assests_directory="){
				input >> dir_assests;	
			}
		}
		std::cout << resX << " is the X Resolution " << std::endl;
		std::cout << resY << " is the Y Resolution " << std::endl;
		std::cout << dir_assests << " is the assest directory." << std::endl;
	}
	return 0;
}
