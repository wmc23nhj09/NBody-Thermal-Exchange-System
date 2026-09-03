#pragma once
#include <SDL3/SDL.h>
#include "blocks.h"
#include <vector>

class Render {
public:
	SDL_Renderer* renderer;

	Render(SDL_Renderer* renderer);

	void update(std::vector<ThermalBlocks> blocksinuse, SDL_FRect mouse, BlockManager blockrender, bool Create, bool Destroy);
};