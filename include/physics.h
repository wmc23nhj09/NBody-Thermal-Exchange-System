#pragma once
#include "SDL3/SDL.h"
#include "blocks.h"

class Physics {

public:
	void DeepSpaceHeatTransfer(std::vector <ThermalBlocks > * block, float dt, float transferspeed, double sigma, double emissivety);
	//float HeatTransfer();
	void AddConduction(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, float dt, float transferspeed, std::vector<float>& tempsToadd, BlockManager& blockUser);
	void AddRadiation(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, float dt, float transferspeed, float sigma, std::vector<float>& tempsToadd, BlockManager& blockUser);
	void GetRGB(ThermalBlocks* blocks);;
	void getCoolingConstant(double sigma, std::vector<ThermalBlocks>& blocksinuse);
};