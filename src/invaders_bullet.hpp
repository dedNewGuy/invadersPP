#pragma once
#include <SDL2/SDL.h>

#define MAX_BULLET 32
#define BULLET_COUNTDOWN 1 // 2 seconds

struct Bullet {
	SDL_FRect bullet[MAX_BULLET]{};
	int bullet_count = 0;
	float speed = 200;
	float bullet_time_acc = 2;

	void add(SDL_FRect spaceship)
	{
		if (bullet_count >= MAX_BULLET) return;

		SDL_FRect b = {
			spaceship.x + spaceship.w / 2,
			spaceship.y,
			10,
			10
		};

		for (int i = 0; i < MAX_BULLET; ++i) {
			if (bullet[i].w <= 0) {
				bullet[i] = b;
				bullet_count++;
				break;
			}
		}
		bullet_time_acc = 0;
	}

	void update(float deltatime)
	{
		bullet_time_acc += deltatime;
		for (int i = 0; i < MAX_BULLET; ++i) {
			if (bullet[i].w <= 0) continue;
			bullet[i].y -= speed * deltatime;
			if (bullet[i].y < 0) {
				bullet[i].w = -1; 
				bullet_count--;
			}
		}
	}

	void render(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0x00);
		for (int i = 0; i < MAX_BULLET; ++i) {
			if (bullet[i].w <= 0) continue;
			SDL_RenderFillRectF(renderer, &bullet[i]);
		}
	}
};
