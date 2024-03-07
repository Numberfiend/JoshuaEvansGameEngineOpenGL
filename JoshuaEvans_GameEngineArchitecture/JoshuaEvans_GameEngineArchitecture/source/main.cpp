#define SDL_MAIN_HANDLED
#include "GameEngine.h"
#include "FontRenderer.h"
#include <iostream>

using namespace std;
#include <sstream>
SDL_Renderer* renderer = nullptr;
SDL_Surface* screensurface = nullptr;
using namespace GE;

int main() {
	// Create a game engine object
	std::unique_ptr<FontRenderer> fontRenderer;
	fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
	GameEngine ge;
	fontRenderer->init();
	if (!ge.init()) {
		display_info_message("Couldn't start SDL.  Check console output for more details");

		return -1;
	}

	Uint32 last_time = SDL_GetTicks(), current_time = 0;
	int frame_count = 0;

	// Main loop
	while (ge.keep_running()) {
		ge.update();
		ge.draw();
		frame_count++;
		current_time = SDL_GetTicks();
		if (current_time - last_time > 1000) {
			std::ostringstream msg;
			msg << "FPS = " << frame_count;
			stringstream stream;
			stream << frame_count;
			string stringframe;
			stream >> stringframe;
			fontRenderer->render(to_string(frame_count));


			ge.setwindowtitle(msg.str().c_str());
			frame_count = 0;
			last_time = current_time;
		}

	}

	// Destroy game engine
	ge.shutdown();

	return 0;
}