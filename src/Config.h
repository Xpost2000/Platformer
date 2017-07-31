#ifndef CONFIG_H
#define CONFIG_H
#include <fstream>
#include <string>
// read from a directory to collect data for the game.
class Config{
	public:
		void read_config();
		std::string get_game_name() { return game_name; }
		std::string get_texture_dir() { return texture_dir; }
		std::string get_level_dir() { return level_dir; }
		std::string get_sounds_dir() { return sounds_dir; }
		int get_vsync_flag() { return vsync; }
		int get_window_width() { return window_width; }
		int get_window_height() { return window_height; }
	private:
		// data for the game.
		// initialize to default values.
		//
		std::string game_name="engine";
		int vsync=1;
		int window_width=1024;
		int window_height=768;
		std::string texture_dir="";
		std::string level_dir="";
		std::string sounds_dir="";
};
#endif
