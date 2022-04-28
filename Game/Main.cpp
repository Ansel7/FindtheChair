#include "Game.h"

#ifdef __cplusplus
extern "C" {
#endif

int IRRCALLCONV main(int argc, char* argv[]){
	Game game;
	return game.run();
}

#ifdef __cplusplus
}
#endif