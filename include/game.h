#pragma once
#include "vector"
#include "SDL3/SDL.h"
#include "blocks.h"
#include "physics.h"
#include "UI.h"
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
	std::vector<double> tempsToadd;
	float distanceoffsetx;
	float distanceoffsety;
	SDL_Event e;
	BlockManager blockrender;
	Physics physicswork;
	UI Ui;
	SDL_FRect mouse;
	Uint32 mouseMap;
	double dt;
	float SimSpeed;
	float Simdt;
	float transferspeed;
	const double sigma;
	int emissivety;
	Uint64 framesbefore;
	Uint64 framesnow;
	float CreationTemp;
	float CreationMass;
	float CreationEmissivety;
	float CreationSpecificHeatEnergy;
	float CreationDensity;
	float CreationKC;
	bool Create;
	bool Destroy;
	bool DSC;
	bool Radiation;
	bool Conduction;
	const SDL_DisplayMode* dm;
};