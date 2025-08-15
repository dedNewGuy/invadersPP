#pragma once

#include <SDL2/SDL.h>

#define MONSTER_COUNT 15

struct Monster {
	SDL_FRect rect;
	bool is_dead;
};

struct Monsters {
	Monster monsters[MONSTER_COUNT]{};
	int count = 0;

	void init()
	{
		int row = 3;
		int col = 5;

		float monster_width = 50;
		float monster_height = 50;
		for (int i = 0; i < row; ++i) {
			Monster monster;
			for (int j = 0; j < col; ++j) {
				float x = j * monster_width + 20;
				float y = i * monster_height + 20;
				SDL_FRect rect = {
					x, y,
					monster_width,
					monster_height
				};
				monster.rect = rect;
				monster.is_dead = false;
				monsters[count++] = monster;
			}
		}
	}

	void render(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0x00);
		for (int i = 0; i < MONSTER_COUNT; ++i) {
			if (monsters[i].is_dead) continue;
			SDL_RenderFillRectF(renderer, &monsters[i].rect);
		}
	}
  
};
