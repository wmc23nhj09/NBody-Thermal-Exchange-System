#include "physics.h"
#include <SDL3/SDL.h>
#include "vector"
#include "iostream"
#include "algorithm"

void Physics::DeepSpaceHeatTransfer(std::vector<ThermalBlocks>* blocks, float dt, float transferspeed, float sigma, int emissivety) {
	for (auto ba = blocks->begin(); ba != blocks->end(); ba++) {

		std::cout << "Before: " << ba->physics.temp << "\n";

		float CoolingFactor = cbrt(1 + (3 * ba->physics.k * pow(ba->physics.temp,3) * dt));
		float NewTemp = ba->physics.temp / CoolingFactor;
		ba->physics.temp = NewTemp;

		std::cout << "After: " << ba->physics.temp << "\n";
	}
}

void Physics::AddToTemp(std::vector<ThermalBlocks>* block, float dt, float transferspeed, float sigma) {
	BlockManager blockUser;
	std::vector<float> tempsToadd(block->size(), 0.0f);
	for (size_t ba = 0; ba < block->size(); ba++) {
		for (size_t bb = ba + 1; bb < block->size(); bb++) {

			if (blockUser.getTouchingIndexes((*block)[ba], (*block)[bb])) {
				float TempDif = blockUser.GetTempDif((*block)[ba].physics.temp, (*block)[bb].physics.temp);

				float k = ((*block)[ba].physics.k + (*block)[bb].physics.k)/2;
				float A = std::min((*block)[ba].physics.A, (*block)[bb].physics.A);
				float d = ((*block)[ba].physics.d + (*block)[bb].physics.d) / 2;
				
				float heatRate = (k * A * TempDif) / d;
				float Q = heatRate * dt * transferspeed;

				tempsToadd[ba] -= Q / ((*block)[ba].physics.mass * (*block)[ba].physics.specific_heat_energy);
				tempsToadd[bb] += Q / ((*block)[bb].physics.mass * (*block)[bb].physics.specific_heat_energy);
			}
			else {
				//Radiation Heat Physics Here
				float EFF = sqrt((*block)[ba].physics.A * (*block)[bb].physics.A);
				float distanceSquared = pow((*block)[ba].render.rect.x - (*block)[bb].render.rect.x, 2) + pow((*block)[ba].render.rect.y - (*block)[bb].render.rect.y, 2);
				float radiationCoefficient = sigma * (*block)[ba].physics.emissivety *
					(*block)[bb].physics.emissivety *
					EFF *
					(pow((*block)[ba].physics.temp, 4) - pow((*block)[bb].physics.temp, 4));

				float radiationpower = radiationCoefficient / (distanceSquared);

				tempsToadd[ba] -= radiationpower / ((*block)[ba].physics.mass * (*block)[ba].physics.specific_heat_energy);
				tempsToadd[bb] += radiationpower / ((*block)[bb].physics.mass * (*block)[bb].physics.specific_heat_energy);
			}
		}
	}

	for (size_t i = 0; i < block->size(); i++) {
		(*block)[i].physics.temp += tempsToadd[i];
	}
}

void Physics::GetRGB(ThermalBlocks* BlockManager) {
	float r = 0.0f, g = 0.0f, b = 0.0f;

	float T = BlockManager->physics.temp / 100.0f; // FIXED SCALE

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

	BlockManager->render.rgb = {
		(Uint32)std::clamp(r, 0.0f, 255.0f),
		(Uint32)std::clamp(g, 0.0f, 255.0f),
		(Uint32)std::clamp(b, 0.0f, 255.0f)
	};
}

void Physics::getCoolingConstant(float sigma, std::vector<ThermalBlocks>& blocksinuse) {
	for (auto& block : blocksinuse) {
		block.physics.k = (block.physics.emissivety * sigma * block.physics.A) / (block.physics.mass * block.physics.specific_heat_energy);
	}
}