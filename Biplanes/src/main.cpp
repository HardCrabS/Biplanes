#include "Game.h"
#include "Logger.h"

int main()
{
	try {
		Game game;
		game.run();
	}
	catch (const std::exception & e) {
		logError(e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}