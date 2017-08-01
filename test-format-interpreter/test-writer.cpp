#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/*
 * this program will convert a standard ascii level tilemap into
 * a more data based approach format.
 *
 * for example
 * # which is a block becomss
 * block w h x y r g b
 *
 * This is a prototype translator.
 *
 * A much more better implementation and possibly a GUI interface will be implemented in the following weeks.
 */
int main (int argc, char** argv){
	if( argc < 1 ){
		return -1;
	}else{
		std::vector<std::string> level;
		std::ifstream input(argv[1]);
		std::ofstream out("out-level.fmt");

		std::string temp;
		while( input >> temp ){
			level.push_back(temp);
		}
		input.close();
		for(int i = 0; i < level.size(); ++i){
			for(int j = 0; j < level[i].size(); ++j){
				switch(level[i][j]){
					case '#':
						out << "block 20 20 " << std::to_string(j*20) << " " << std::to_string(i*20) << std::endl; 
						break;
					case '@':
						out << "player_spawn " << std::to_string(j*20) << " " << std::to_string(i*20) << std::endl;
						break;
					default:
						break;
				}
			}
		}
		out.close();
	}
	return 0;
}
