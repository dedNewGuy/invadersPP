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

	// Key Pressed bool
	bool key_up_pressed = false;
	bool key_left_pressed = false;
	bool key_right_pressed = false;

	// Defined Rect
	SDL_Rect spaceship = {
		375, 525,
		50, 50
	};

	while (is_running) {
		// Rendering
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0x00);
		SDL_RenderFillRect(renderer, &spaceship);

		SDL_RenderPresent(renderer);

		// Updating
		if (key_left_pressed) {
			spaceship.x -= 1;
		} else if (key_right_pressed) {
			spaceship.x += 1;
		}

		// Polling input
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							key_left_pressed = true;
							break;
						case SDLK_RIGHT:
							key_right_pressed = true;
							break;
						case SDLK_UP:
							key_up_pressed = true;
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							key_left_pressed = false;
							break;
						case SDLK_RIGHT:
							key_right_pressed = false;
							break;
						case SDLK_UP:
							key_up_pressed = false;
							break;
					}
					break;
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
