#include <stdlib.h>
#include <stdio.h>
#include "display.hpp"

int main(int /*argc*/, char** /*argv*/)
{
	gp::Display* const display = gp::create_display("Hello gproj!", 800, 600);
	if (display == nullptr)
		return EXIT_FAILURE;

	constexpr const unsigned long kTurnTicks = 512;
	constexpr const unsigned long kColTicks = 64;

	enum Turn {
		kRedTurn,
		kGreenTurn,
		kBlueTurn
	} turn = kRedTurn;

	float red = 0, green = 1.0f, blue = 0;
	
	unsigned long turnticks = SDL_GetTicks();
	unsigned long colticks = turnticks;

	while (update_display(display)) {
		
		if ((SDL_GetTicks() - turnticks) > kTurnTicks) {
			switch (turn) {
			case kRedTurn:
				turn = kGreenTurn;
				blue = 1;
				break;
			case kGreenTurn:
				turn = kBlueTurn;
				red = 1;
				break;
			case kBlueTurn:
				turn = kRedTurn;
				green = 1;
				break;
			}
			turnticks = SDL_GetTicks();
		}

		if ((SDL_GetTicks() - colticks) > kColTicks) {
			switch (turn) {
			case kRedTurn:
				red += 0.1f;
				green -= 0.1f;
				break;
			case kGreenTurn:
				green += 0.1f;
				blue -= 0.1f;
				break;
			case kBlueTurn:
				blue += 0.1f;
				red -= 0.1f;
				break;
			}
			colticks = SDL_GetTicks();
		}

		gp::clear_display(red, green, blue, 1.0f);
	}

	gp::destroy_display(display);
	return EXIT_SUCCESS;
}



