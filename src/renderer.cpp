#include "renderer.h"
#include "blocks.h"
#include <cmath>
#include <iostream>

Render::Render(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Render::update(std::vector<ThermalBlocks> blocksinuse, SDL_FRect mouse, BlockManager blockrender, bool Create, bool Destroy, const int WINWIDTH, const int WINHEIGHT, Cone& ConeHolder) {
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


	if (!(ConeHolder.Angle == -1)) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		double raylength = std::hypot(WINWIDTH, WINHEIGHT);

		double leftx = ConeHolder.Lx + cos(ConeHolder.Angle) * raylength;
		double lefty = ConeHolder.Ly + sin(ConeHolder.Angle) * raylength;

		double rightx = ConeHolder.Rx + cos(ConeHolder.Angle) * raylength;
		double righty = ConeHolder.Ry + sin(ConeHolder.Angle) * raylength;

		SDL_Vertex Verticies[4]{
			{{ConeHolder.Lx, ConeHolder.Ly} , {0.0f, 255.0f, 0.0f, 0.5f}, {0.0f , 0.0f} },
			{{ConeHolder.Rx, ConeHolder.Ry} , {0.0f, 255.0f, 0.0f, 0.5f}, {0.0f , 0.0f} },
			{{leftx, lefty}, {0.0f, 255.0f, 0.0f, 0.0f}, {0.0f , 0.5f} },
			{{rightx, righty}, {0.0f, 255.0f, 0.0f, 0.0f}, {0.0f , 0.5f} }
		};

		int indices[6] = { 0, 1, 2, 0, 2, 3 };
		/*Evidence suggest start and end points are of equal distance, however, visually they seem to converge
		Some Evidence suggests that at end point they get bigger, however I'd suggest taking the top claim as more creditable*/

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderGeometry(renderer, nullptr, Verticies, 4, indices, 6);

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	}

}