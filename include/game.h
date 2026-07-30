#pragma once
#include "vector"
#include "SDL3/SDL.h"
#include "blocks.h"
#include "physics.h"
#include "window.h"
#include "renderer.h"

class Game {
public:
	Game();

	void run();
	void physicsbackground();

private:
	bool running;
	Window window;
	Render renderer;
	std::vector<ThermalBlocks> blocksinuse;
	float distanceoffsetx;
	float distanceoffsety;
	SDL_Event e;
	BlockManager blockrender;
	Physics physicswork;
	SDL_FRect mouse;
	Uint32 mouseMap;
	float dt;
	float SimSpeed;
	float Simdt;
	float transferspeed;
	const float sigma;
	int emissivety;
	Uint64 framesbefore;
	Uint64 framesnow;
};