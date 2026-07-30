#include "SDL3/SDL.h"
#include "game.h"
#include "blocks.h"
#include "physics.h"
#include "iostream"
#include "windows.h"
#include "renderer.h"

//Main Game Class
	//Initliasation when Class runs (__init__) --> In CPP it is referred to as a CONSTRUCTOR CLASS
Game::Game() : running(true),
	window(),
	renderer(window.renderer),
				 //PHYSICS							 //RENDERING											 //INTERACTION
				 //Temp      A   D   Mass E  SHE   K||        RECT						 RGB				 || Held   Down
	blocksinuse({ { {18000, 0.5, 25, 190, 1, 5000, 0.0f}, { {10, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} } }),
	distanceoffsetx(-1.0f),
	distanceoffsety(-1.0f),
	e{},
	blockrender(),
	physicswork(),
	mouse({ 0,0,1,1 }),
	mouseMap(),
	dt(),
	SimSpeed(100.0f),
	Simdt(),
	sigma(5.67e-8),
	emissivety(1),
	transferspeed(1),
	framesbefore(),
	framesnow()
{
};

//Main Game Loop
void Game::run() {
	framesbefore = SDL_GetPerformanceCounter();
	while (running) {
		framesnow = SDL_GetPerformanceCounter();

		dt = (float)(framesnow - framesbefore) / SDL_GetPerformanceFrequency();
		Simdt = dt * SimSpeed;
		framesbefore = framesnow;
		mouseMap = SDL_GetMouseState(&mouse.x, &mouse.y);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
				running = false;
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				for (auto& b : blocksinuse) {
					blockrender.getHeldState(mouse, &b);
				}
			}

			else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				for (auto& b : blocksinuse) {
					b.interaction.held = false;
				}
				distanceoffsetx = -1.0f;
				distanceoffsety = -1.0f;
			}
		}
		for (auto& b : blocksinuse) {
			blockrender.moveBlocks(&b, mouse, distanceoffsetx, distanceoffsety);
		}
		physicsbackground();
		renderer.update(blocksinuse, mouse, blockrender);
	}
}

void Game::physicsbackground() {

	physicswork.getCoolingConstant(sigma, blocksinuse);
	physicswork.DeepSpaceHeatTransfer(&blocksinuse, Simdt, transferspeed, sigma, emissivety);
	physicswork.AddToTemp(&blocksinuse, Simdt, transferspeed, sigma);

	for (auto b = blocksinuse.begin(); b != blocksinuse.end(); b++) {
		physicswork.GetRGB(&(*b));
	}
}