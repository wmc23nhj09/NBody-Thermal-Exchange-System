#pragma once

#include "SDL3/SDL.h"
#include "vector"

struct blockindexes {
	int blocka;
	int blockb;
};

struct RGB {
	Uint32 r;
	Uint32 g;
	Uint32 b;
};

struct PhysicsState {
	double temp;
	double A;
	double d;
	double mass;
	double emissivety;
	double specific_heat_energy;
	double k;
	double kC;
};

struct RenderingState {
	SDL_FRect rect;
	RGB rgb;
};

struct InteractionState {
	bool held;
	bool down;
};

struct ThermalBlocks {
	PhysicsState physics;
	RenderingState render;
	InteractionState interaction;
};

class BlockManager {
public:
	float GetTempDif(double Tempa, double Tempb);
	ThermalBlocks CreateBlock(double temp, SDL_FRect rect, double A, double d, double mass, double emissivety, double specific_heat_energy, double k);
	void renderallblocks(ThermalBlocks blocks, SDL_Renderer* renderer);
	void getHeldState(SDL_FRect mouse, ThermalBlocks* block);
	bool getTouchingIndexes(ThermalBlocks blocka, ThermalBlocks blockb);
	void moveBlocks(ThermalBlocks* blocks, SDL_FRect mouse, float& distanceoffsetx, float& distanceoffsety);
};