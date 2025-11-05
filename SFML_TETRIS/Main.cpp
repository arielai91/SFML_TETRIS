#include "Global.h"
#include "Game.h"

/**
 * @brief Entry point of the Tetris game application
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return int Exit status code (0 for success, non-zero for error)
 */
int main(int argc, char* argv[])
{
	try {
		// Initialize and run the game
		Game game;
		game.run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown fatal error occurred" << std::endl;
		return EXIT_FAILURE;
	}
}

