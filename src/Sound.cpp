#include "Sound.h"

// forward declartion to avoid errors
std::map<std::string, Mix_Music*> Sound::music;
std::map<std::string, Mix_Chunk*> Sound::chunks;

void Sound::load_sound(std::string fPath, std::string key){
	Mix_Chunk* temp = Mix_LoadWAV(fPath.c_str());
	chunks.emplace(std::make_pair(key, temp));
}

void Sound::load_music(std::string fPath, std::string key){
	Mix_Music* temp = Mix_LoadMUS(fPath.c_str());
	music.emplace(std::make_pair(key, temp));
}

void Sound::play_sound(std::string keyName, int volume, int channel, int loops){
	Mix_Volume(channel, volume);
	Mix_PlayChannel(channel, chunks[keyName], loops);
}

void Sound::play_music( std::string keyName, int loops ){
	Mix_PlayMusic(music[keyName], loops);
}

void Sound::free_memory(){
	printf("Freeing Memory\n");
	// I'm going to hope this achieves it's purposes.
	for(auto& m : music){
		Mix_FreeMusic(m.second);
	}
	for(auto& c : chunks){
		Mix_FreeChunk(c.second);
	}
	Mix_Quit();
}

bool Sound::init( int frequency, Uint16 fmt, int channels, int chunksize ){
	int res=Mix_OpenAudio(frequency, fmt, channels, chunksize);
	if(res==0){return true;}else{return false;}	
}
