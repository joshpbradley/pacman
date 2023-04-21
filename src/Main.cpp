/// <author>
/// Joshua Bradley
/// </author>

#include <time.h>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"

#include "ResourceManager.h"
#include "PacMan.h"
#include "Drawer.h"

extern const unsigned char kXOffset = 177;
extern const unsigned char kYOffset = 60;

const unsigned short kWindowWidth = 1024;
const unsigned short kWindowHeight = 768;
const float kUpdateDelay = 1000.f / 60.f;

int main(int argc, char** args) {
	// Initialises SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		assert(0 && "Failed to initialize video!");
		exit(-1);
	}

	// Closes SDL on program exit.
	at_quick_exit(SDL_Quit);
	atexit(SDL_Quit);

	// Initialise random seed.
	srand(static_cast<unsigned int>(time(0)));
	
	// Generates viewport with dimension 1024px x 768px.
	SDL_Window* window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWindowWidth, kWindowHeight, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!window) {
		assert(0 && "Failed to create window!");
		exit(EXIT_FAILURE);
	}

	if (!renderer) {
		assert(0 && "Failed to create renderer!");
		exit(EXIT_FAILURE);
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (TTF_Init() == -1) {
		assert(0 && "Failed to create ttf!");
		exit(EXIT_FAILURE);
	}

	// Sets the font used in the game UI.
	try {
		ResourceManager::Instance().set_font("Fonts\\Pac-Man.ttf");
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	auto drawer = new Drawer(renderer);
	PacMan pacman = PacMan::Instance(drawer);

	auto last_ticks = SDL_GetTicks();
	SDL_Event event;

  // Sets the colour to black upon clearing the viewport.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	unsigned int elapsed_millis;

	while (SDL_PollEvent(&event) >= 0) {
		while ((elapsed_millis = SDL_GetTicks() - last_ticks) < kUpdateDelay) {
			SDL_Delay(0);
		}

		// Clears the screen to black.
		SDL_RenderClear(renderer);
		// Adds game elements to the drawing buffer.
		pacman.Draw(elapsed_millis);
		// Draws from the buffer.
		SDL_RenderPresent(renderer);

		if (!pacman.Update(elapsed_millis)) {
			break;
		}

		last_ticks = SDL_GetTicks();
	}

	delete drawer;

	return 0;
}