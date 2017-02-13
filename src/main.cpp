#include <iostream>
#include "exception.hpp"
#include "display.hpp"
#include "resource_manager.hpp"
#include "finally.hpp"
#include "game.hpp"


int main()
{
	try  {
		gp::Display::initialize();
		const auto display_terminator = gp::finally([] {
			gp::Display::terminate();
		});


		gp::ResourceManager::initialize();
		const auto resource_manager_terminator = gp::finally([] {
			gp::ResourceManager::terminate();
		});

		gp::Game game;
		game.run();

		return EXIT_SUCCESS;

	} catch (std::exception& exception) {
		std::cerr << "FATAL EXCEPTION: " << exception.what() << '\n';
	} catch (...) {
		std::cerr << "FATAL UNKNOWN EXCEPTION...\n"; 
	}

	std::cout << "PRESS ENTER TO EXIT\n";
	std::cin.ignore(1);
	return EXIT_FAILURE;
}

