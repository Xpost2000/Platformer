#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct block{
	block(int x, int y, int w, int h) : x(x), y(y) , w(w), h(h){}
	int x, y;
	int w, h;
};

int player_spawnX=0;
int player_spawnY=0;

int main(int argc, char** argv){
	if(argc < 1){
		return -1;
	}else{
		std::vector<block> blocks;
		std::ifstream input(argv[1]);
		std::string identifier;
		while( input >> identifier ){
			if(identifier == "block"){
				int w ;
				int h ; 
				int x ;
				int y ;
				input >> w;
				input >> h;
				input >> x;
				input >> y;
				blocks.push_back(block(x, y, w, h));
				std::cout << "Block(w, h, x, y) : " << w << "," << h << "," << x << "," << y << std::endl;
			}
			if(identifier == "player_spawn"){
				input >> player_spawnX;
				input >> player_spawnY;
				std::cout << "Player spawns at :: " << player_spawnX << ", " << player_spawnY << std::endl; 
			}
		}
		input.close();
	}
	return 0;
}
