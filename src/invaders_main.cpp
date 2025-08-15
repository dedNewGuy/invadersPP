#include <iostream>
#include <SDL2/SDL.h>

#include "invaders_bullet.hpp"
#include "invaders_monster.hpp"

#define WINDOW_TITLE "InvadersPP"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 60
#define FRAMERATE (1000 / FPS)

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

	// Defined Spaceship
	SDL_FRect spaceship = {
		375, 525,
		50, 50
	};
	float speed = 0;

	// Defined bullet
	Bullet bullet;

	// Defined monster
	Monsters monsters;
	monsters.init();

	// Time variable
	int last_frame_time = 0;
	float deltatime = 0;

	while (is_running) {
		int waiting_time = FRAMERATE - (SDL_GetTicks() - last_frame_time);
		if (waiting_time > 0 && waiting_time <= FRAMERATE)
			SDL_Delay(waiting_time);
		deltatime = (SDL_GetTicks() - last_frame_time) / 1000.0f;
		last_frame_time = SDL_GetTicks();

		// Rendering
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0x00);
		SDL_RenderFillRectF(renderer, &spaceship);

		bullet.render(renderer);
		monsters.render(renderer);

		SDL_RenderPresent(renderer);

		speed = 200 * deltatime;
		SDL_Log("Spaceship x: %f\n", spaceship.x);
		SDL_Log("Speed: %f\n", speed);
		SDL_Log("Deltatime: %f\n", deltatime);
		SDL_Log("key_left_pressed: %d\n", key_left_pressed);
		SDL_Log("key_right_pressed: %d\n", key_right_pressed);
		SDL_Log("key_up_pressed: %d\n", key_up_pressed);
		SDL_Log("Bullet count: %d\n", bullet.bullet_count);

		// Updating
		bullet.update(deltatime);
		
		if (key_left_pressed) {
			spaceship.x -= speed;
		} else if (key_right_pressed) {
			spaceship.x += speed;
		} 

		if (key_up_pressed) {
			if (bullet.bullet_time_acc >= BULLET_COUNTDOWN) {
				bullet.add(spaceship);
			}
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
