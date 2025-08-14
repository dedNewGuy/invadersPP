#pragma once
#include <SDL2/SDL.h>

#define MAX_BULLET 32

struct Bullet {
	SDL_FRect bullet[MAX_BULLET];
	int bullet_count;

	void add(SDL_FRect spaceship)
	{
		if (bullet_count >= MAX_BULLET) return;

		SDL_FRect b = {
			spaceship.x + spaceship.w / 2,
			spaceship.y,
			10,
			10
		};

		bullet[bullet_count++] = b;
	}

	void render(SDL_Renderer *renderer, float bullet_speed)
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
		for (int i = 0; i < bullet_count; ++i) {
			bullet[i].y -= bullet_speed;
			SDL_RenderFillRectF(renderer, &bullet[i]);
		}
	}
};
