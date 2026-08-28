#include "physics.h"
#include <SDL3/SDL.h>
#include "vector"
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include "iostream"
#include "algorithm"

void Physics::DeepSpaceHeatTransfer(std::vector<ThermalBlocks>* blocks, float dt, float transferspeed, double sigma, double emissivety) {
	for (auto ba = blocks->begin(); ba != blocks->end(); ++ba) {
		double old_temp = ba->physics.temp;
		double space_temp = 2.7;

		double temp_fourthed = old_temp * old_temp * old_temp * old_temp;
		double space4 = space_temp * space_temp * space_temp * space_temp;

		double deltaTemp = ba->physics.k * (temp_fourthed - space4) * dt;

		ba->physics.temp -= deltaTemp;
	}
}

void Physics::AddConduction(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, float dt, float transferspeed, std::vector<double>& tempsToadd, BlockManager& blockUser) {
	
	float TempDif = blockUser.GetTempDif(BlockA.physics.temp, BlockB.physics.temp);

	float k = (BlockA.physics.kC + BlockB.physics.kC)/2;
	float A = std::min(BlockA.physics.A, BlockB.physics.A);
	float d = (BlockA.physics.d + BlockB.physics.d) / 2;
			
	float heatRate = (k * A * TempDif) / d;
	float Q = heatRate * dt * transferspeed;

	Q = abs(Q);

	if (BlockA.physics.temp > BlockB.physics.temp) {
		tempsToadd[ba] -= Q / (BlockA.physics.mass * BlockA.physics.specific_heat_energy);
		tempsToadd[bb] += Q / (BlockB.physics.mass * BlockB.physics.specific_heat_energy);
	}
	else {
		tempsToadd[ba] += Q / (BlockA.physics.mass * BlockA.physics.specific_heat_energy);
		tempsToadd[bb] -= Q / (BlockB.physics.mass * BlockB.physics.specific_heat_energy);
	}
}

void Physics::AddRadiation(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, float dt, float transferspeed, double sigma, std::vector<double>& tempsToadd, BlockManager& blockUser) {
	float EFF = sqrt(BlockA.physics.A * BlockB.physics.A);

	float distanceSquared = pow(BlockA.render.rect.x - BlockB.render.rect.x, 2) + pow(BlockA.render.rect.y - BlockB.render.rect.y, 2);
	float radiationCoefficient = sigma * BlockA.physics.emissivety *
		BlockB.physics.emissivety *
		EFF *
		(pow(BlockA.physics.temp, 4) - pow(BlockB.physics.temp, 4));

	//radiationCoefficient = abs(radiationCoefficient);

	if (distanceSquared < 1.0f){
		distanceSquared = 1.0f;
	}
	float radiationpower = radiationCoefficient / (distanceSquared);
	float Q = radiationpower * dt * transferspeed;

	Q = abs(Q);


	if (BlockA.physics.temp > BlockB.physics.temp) {
		tempsToadd[ba] -= Q / (BlockA.physics.mass * BlockA.physics.specific_heat_energy);
		tempsToadd[bb] += Q / (BlockB.physics.mass * BlockB.physics.specific_heat_energy);
	}
	else {
		tempsToadd[ba] += Q / (BlockA.physics.mass * BlockA.physics.specific_heat_energy);
		tempsToadd[bb] -= Q / (BlockB.physics.mass * BlockB.physics.specific_heat_energy);
	}
}

void Physics::GetRGB(ThermalBlocks* block) {
	float r = 0.0f, g = 0.0f, b = 0.0f;

	float T = block->physics.temp / 100.0f; // FIXED SCALE

	if (T <= 0) T = 0.01f;

	// Red
	if (T <= 66)
		r = 255;
	else
		r = 329.698727446 * pow(T - 60, -0.1332047592);

	// Green
	if (T <= 66)
		g = 99.4708025861 * log(T) - 161.1195681661;
	else
		g = 288.1221695283 * pow(T - 60, -0.0755148492);

	// Blue
	if (T >= 19 && T <= 66)
		b = 138.5177312231 * log(T - 10) - 305.0447927307;
	else if (T > 66)
		b = 255;
	else
		b = 0;

	block->render.rgb = {
		(Uint32)std::clamp(r, 0.0f, 255.0f),
		(Uint32)std::clamp(g, 0.0f, 255.0f),
		(Uint32)std::clamp(b, 0.0f, 255.0f)
	};
}

void Physics::getCoolingConstant(double sigma, std::vector<ThermalBlocks>& blocksinuse) {
	for (auto& block : blocksinuse) {
		block.physics.k = (block.physics.emissivety * sigma * block.physics.A) / (block.physics.mass * block.physics.specific_heat_energy);
	}
}