#include <iostream>
#include "exception.hpp"
#include "game.hpp"

int main()
{
	try  {
		gp::Game game;
		game.run();
		return EXIT_SUCCESS;
	} catch (std::exception& exception) {
		std::cerr << "FATAL EXCEPTION: " << exception.what() << '\n';
	} catch (...) {
		std::cerr << "FATAL UNKNOWN EXCEPTION...\n"; 
	}

	system("pause");
	return EXIT_FAILURE;
}

