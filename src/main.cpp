#include "Game.h"
int main(int argc, char** argv){
	Game *game;
	if(argc < 2){
		game = new Game();
	}else{
		game = new Game(argc, argv);
	}
	game->run();
	delete game;
	SDL_Quit();
	return 0;
}
