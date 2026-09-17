#pragma once
#include "blocks.h"
#include "renderer.h"

class Physics {

public:
	void DeepSpaceHeatTransfer(std::vector <ThermalBlocks> * block, double dt, double sigma, double emissivety);
	//float HeatTransfer();
	void AddConduction(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, float transferspeed, std::vector<double>& tempsToadd, BlockManager& blockUser);
	void AddRadiation(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, double sigma, std::vector<double>& tempsToadd, BlockManager& blockUser, std::vector<double>& SpecificBlockDists);
	void GetRGB(ThermalBlocks* blocks);
	void getCoolingConstant(double sigma, std::vector<ThermalBlocks>& blocksinuse);
	void CheckOccultation(std::vector<ThermalBlocks>& blocksinuse, std::vector<double>& SpecificBlockDists, int i, std::vector<double>& tempsToadd, Cone& ConeHolder, bool& showShadow, int index);
	float setdt(std::vector<ThermalBlocks>& block, double sigma, BlockManager& blockUser);
};