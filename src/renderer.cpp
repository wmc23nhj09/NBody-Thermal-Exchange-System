#include "renderer.h"
#include "blocks.h"

Render::Render(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Render::update(std::vector<ThermalBlocks> blocksinuse, SDL_FRect mouse, BlockManager blockrender, bool Create, bool Destroy, const int WINWIDTH, const int WINHEIGHT) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (auto& b : blocksinuse) {
		blockrender.renderallblocks(b, renderer);
	}

	SDL_FRect temp = { 0, (float)0.6639*WINHEIGHT, (float)0.7802*WINWIDTH, (float)0.3361*WINHEIGHT};
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

	temp = { (float)0.7802 * WINWIDTH, (float)0.6639 * WINHEIGHT, (float)1 * WINWIDTH, (float)1 * WINHEIGHT };

	SDL_RenderFillRect(renderer, &temp);

	temp = { (float)0.7802*WINWIDTH, 0, (float)1*WINWIDTH, (float)0.6639 * WINHEIGHT };

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);

	SDL_RenderFillRect(renderer, &temp);
}