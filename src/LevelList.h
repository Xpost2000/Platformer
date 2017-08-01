#ifndef LEVEL_LIST_H
#define LEVEL_LIST_H
#include <fstream>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>
class LevelListFile{
	// This file reads the level list and passes on the directories
	// to a level class which will read the file itself and
	// process it approprietely.
	//  This is just a way so I don't hardcode all my levels.
	public:
		std::string directory;
		std::vector<std::string> entries;
		void read(std::string directory){
			this->directory = directory;
			list.open(this->directory.c_str());
			if(list.good()){
				std::string temp;
				while(list >> temp){
					entries.push_back(temp);
				}
			}else{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error : Game couldn't find level list.", "Level list not found.", NULL);
				return;
			}
		}
	private:
		std::ifstream list;
};
#endif
