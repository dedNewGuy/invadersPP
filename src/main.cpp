#include <iostream>
#include <SDL2/SDL.h>

#define WINDOW_TITLE "InvadersPP"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	bool is_running = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Failed to init sdl: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  WINDOW_WIDTH, WINDOW_HEIGHT,
							  0);
	if (window == NULL) {
		SDL_Log("Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	while (is_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					is_running = false;
					break;
			}
		}
	}

	SDL_DestroyWindow(window);
	return 0;
}
