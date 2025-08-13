#include <SDL2/SDL.h>

#define WINDOW_TITLE "InvadersPP"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	bool is_running = true;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Failed to init sdl: %s\n", SDL_GetError());
		return 1;
	}

	if (SDL_CreateWindowAndRenderer(
        WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        &window, &renderer) < 0) {
		SDL_Log("Failed to create window and renderer: %s\n", SDL_GetError());
		return 1;
	}

	SDL_SetWindowTitle(window, WINDOW_TITLE);

	// Defined Rect
	SDL_Rect rect = {
		10, 20,
		100, 50
	};

	while (is_running) {
		// Render screen black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_RenderPresent(renderer);

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
	SDL_DestroyRenderer(renderer);
	return 0;
}
