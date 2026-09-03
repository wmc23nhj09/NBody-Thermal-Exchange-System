#include "renderer.h"
#include "blocks.h"

Render::Render(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Render::update(std::vector<ThermalBlocks> blocksinuse, SDL_FRect mouse, BlockManager blockrender, bool Create, bool Destroy) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (auto& b : blocksinuse) {
		blockrender.renderallblocks(b, renderer);
	}

	SDL_FRect temp = {0, 717, 1498, 1080-717};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &mouse);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
	SDL_RenderFillRect(renderer, &temp);

	if (Create) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
	}
	else if (Destroy) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 128);
	}

	temp = {1498, 717, 1920, 1080};

	SDL_RenderFillRect(renderer, &temp);
}