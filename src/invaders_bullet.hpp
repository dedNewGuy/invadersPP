#pragma once
#include <SDL2/SDL.h>

#define MAX_BULLET 32

struct Bullet {
	SDL_FRect bullet[MAX_BULLET]{};
	int bullet_count = 0;
	float speed = 200;

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

	void update(float deltatime)
	{
		for (int i = 0; i < bullet_count; ++i) {
			bullet[i].y -= speed * deltatime;
		}
	}

	void render(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
		for (int i = 0; i < bullet_count; ++i) {
			SDL_RenderFillRectF(renderer, &bullet[i]);
		}
	}
};
