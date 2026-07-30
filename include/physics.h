#pragma once
#include "SDL3/SDL.h"
#include "blocks.h"

class Physics {

public:
	void DeepSpaceHeatTransfer(std::vector <ThermalBlocks > * block, float dt, float transferspeed, float sigma, int emissivety);
	//float HeatTransfer();
	void AddToTemp(std::vector<ThermalBlocks>* block, float dt, float transferspeed, float sigma);
	void GetRGB(ThermalBlocks* blocks);;
	void getCoolingConstant(float sigma, std::vector<ThermalBlocks>& blocksinuse);
};