#include "Config.h"
#include <SDL2/SDL.h>

void Config::read_config(){
	std::ifstream config("settings//cfg//settings.cfg");
	if(!config.good()){
		SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR,
				"Fatal error : Game could not find configuration file.",
				"Please reinstall this game for the configuration file.", NULL);
		exit(-1);
		return;
	}else{
		std::string token;
		std::string garbage;
		while( config >> token ){
			if(token == "##" || token == "#" || token == "//"){
				// comment is pointless.
				std::getline(config, garbage);
			}
			if(token == "window_w=" || token=="window_w"){
				config >> window_width;
			}
			if(token == "window_h=" || token=="window_h"){
				config >> window_height;
			}
			if(token == "game_name" || token == "game_name="){
				std::getline(config, game_name);
				#ifdef __linux__
				// I'm going to append a null terminating character cause it seems that Linux doesn't seem to null terminate a string.
				game_name += '\0';
				#endif
			}
			if(token == "texture_dir=" || token == "texture_dir"){
				config >> texture_dir;
			}
			if(token == "level_dir=" || token == "level_dir"){
				config >> level_dir;
			}
			if(token == "sounds_dir=" || token == "sounds_dir"){
				config >> sounds_dir;
			}
			if(token == "vsync-mode=" || token == "vsync-mode"){
				config >> vsync;
			}
			if(token=="levellist-dir=" || token=="levellist-dir"){
				config >> lvllist_dir;
			}
			if(token=="levellist-file=" || token=="levellist-file"){
				config >> lvllist_file;
			}
		}
	}
}
