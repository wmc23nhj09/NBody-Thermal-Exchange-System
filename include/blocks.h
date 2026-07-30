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
	float temp;
	float A;
	float d;
	double mass;
	float emissivety;
	float specific_heat_energy;
	float k;
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
	float GetTempDif(float Tempa, float Tempb);
	ThermalBlocks CreateBlock(float temp, SDL_FRect rect, float A, float d, double mass, float emissivety, float specific_heat_energy, float k);
	void renderallblocks(ThermalBlocks blocks, SDL_Renderer* renderer);
	void getHeldState(SDL_FRect mouse, ThermalBlocks* block);
	bool getTouchingIndexes(ThermalBlocks blocka, ThermalBlocks blockb);
	void moveBlocks(ThermalBlocks* blocks, SDL_FRect mouse, float& distanceoffsetx, float& distanceoffsety);
};