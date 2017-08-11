#ifndef SOUND_H
#define SOUND_H
// it's a static class that can play audio.
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
class Sound{
	public:
		// I'm not going to make a unique ptr wrapper and I want to be safe.
		static void load_sound( std::string fPath, std::string key );
		static void load_music( std::string fPath, std::string key );
		static void play_sound( std::string keyName, int volume=100 ,int channel=0, int loops=0 );
		static void play_music( std::string keyName, int loops=0 );
		static void free_memory();
		static bool init( int frequency=44100, Uint16 fmt=MIX_DEFAULT_FORMAT, int channels=2, int chunksize=2048 );
	private:
		// I'll store the sounds in a hash map
		static std::map<std::string, Mix_Chunk*> chunks;
		static std::map<std::string, Mix_Music*> music;
};
#endif
