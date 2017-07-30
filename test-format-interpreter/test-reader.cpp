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
		bool found_player_spawn=false;
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
			}
			if(identifier == "player_spawn"){
				if(found_player_spawn){
					std::cout << "Warning(C1):: More than one player spawn found.\n";
				}else{
				input >> player_spawnX;
				input >> player_spawnY;
				found_player_spawn = 1;
				}
			}
		}
		input.close();
	}
	return 0;
}
