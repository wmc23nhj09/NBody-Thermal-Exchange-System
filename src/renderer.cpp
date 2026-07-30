#include "renderer.h"
#include "blocks.h"

Render::Render(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Render::update(std::vector<ThermalBlocks> blocksinuse, SDL_FRect mouse, BlockManager blockrender) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (auto& b : blocksinuse) {
		blockrender.renderallblocks(b, renderer);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &mouse);
	SDL_RenderPresent(renderer);
}