#include "SDL3/SDL.h"
#include "game.h"
#include "blocks.h"
#include "physics.h"
#include "iostream"
#include <conio.h>
#include "renderer.h"

//MAX TEMP : 1.89 x 10 ^ 9

//Main Game Class
	//Initliasation when Class runs (__init__) --> In CPP it is referred to as a CONSTRUCTOR CLASS
Game::Game() : running(true),
	window(),
	renderer(window.renderer),
				 //PHYSICS							 //RENDERING											 //INTERACTION
				 //Temp      A   D   Mass, E  SHE   K  KC||        RECT						 RGB				 || Held   Down
	blocksinuse({ { {12000,   1, 25, 1, 1, 900, 0.0f, 400}, { {10, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} },
				{   {509,     1, 25, 1, 1, 500, 0.0f, 400}, { {50, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} },
				{   {1532,    1, 25, 1, 1, 300, 0.0f, 400}, { {90, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} },
				{   {2,       1, 25, 1, 1, 500, 0.0f, 400},{ {30, 50, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} } }),
	tempsToadd{},
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
	transferspeed(10.0f),
	framesbefore(),
	framesnow()
{
};

//Main Game Loop
void Game::run() {
	framesbefore = SDL_GetPerformanceCounter();
	while (running) {
		framesnow = SDL_GetPerformanceCounter();

		dt = ((float)(framesnow - framesbefore) / SDL_GetPerformanceFrequency())/10.0f;

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
	physicswork.DeepSpaceHeatTransfer(&blocksinuse, dt, transferspeed, sigma, emissivety);
	
	float beforeenergy = 0;
	float afterenergy = 0;
	tempsToadd.assign(blocksinuse.size(), 0.0f);

	for (size_t i = 0; i < blocksinuse.size(); i++) {
		beforeenergy += (blocksinuse[i].physics.specific_heat_energy * blocksinuse[i].physics.mass * blocksinuse[i].physics.temp);
	}

	for (size_t i = 0; i < blocksinuse.size(); i++) {
		for (size_t j = i + 1; j < blocksinuse.size(); j++) {
			if (blockrender.getTouchingIndexes(blocksinuse[i], blocksinuse[j])) {
				physicswork.AddConduction(blocksinuse[i], blocksinuse[j], i, j, dt, transferspeed, tempsToadd, blockrender);
			}
			else {
				physicswork.AddRadiation(blocksinuse[i], blocksinuse[j], i, j, dt, transferspeed, sigma, tempsToadd, blockrender);
			}
		}
	}

	for (size_t i = 0; i < tempsToadd.size(); i++) {
		blocksinuse[i].physics.temp += tempsToadd[i];
		physicswork.GetRGB(&blocksinuse[i]);
		std::cout << blocksinuse[i].physics.temp << '\n';
	}
	

	for (size_t i = 0; i < blocksinuse.size(); i++) {
		afterenergy += (blocksinuse[i].physics.specific_heat_energy * blocksinuse[i].physics.mass * blocksinuse[i].physics.temp);
	}

}