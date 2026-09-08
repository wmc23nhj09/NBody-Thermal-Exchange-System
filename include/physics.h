#pragma once
#include "SDL3/SDL.h"
#include "blocks.h"

class Physics {

public:
	void DeepSpaceHeatTransfer(std::vector <ThermalBlocks> * block, double dt, double sigma, double emissivety);
	//float HeatTransfer();
	void AddConduction(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, float transferspeed, std::vector<double>& tempsToadd, BlockManager& blockUser);
	void AddRadiation(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, double sigma, std::vector<double>& tempsToadd, BlockManager& blockUser);
	void GetRGB(ThermalBlocks* blocks);
	void getCoolingConstant(double sigma, std::vector<ThermalBlocks>& blocksinuse);
	float setdt(std::vector<ThermalBlocks>& block, double sigma, BlockManager& blockUser);
};