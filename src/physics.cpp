#include <physics.h>
#include <renderer.h>
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numbers>

void Physics::DeepSpaceHeatTransfer(std::vector<ThermalBlocks>* blocks, double dt, double sigma, double emissivety) {
	for (auto ba = blocks->begin(); ba != blocks->end(); ++ba) {
		double old_temp = ba->physics.temp;
		double space_temp = 2.7;

		double temp_fourthed = old_temp * old_temp * old_temp * old_temp;
		double space4 = space_temp * space_temp * space_temp * space_temp;

		double deltaTemp = ba->physics.k * (temp_fourthed - space4) * dt;

		ba->physics.temp -= deltaTemp;
	}
}

void Physics::AddConduction(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, float transferspeed, std::vector<double>& tempsToadd, BlockManager& blockUser) {

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

void Physics::AddRadiation(const ThermalBlocks& BlockA, const ThermalBlocks& BlockB, size_t& ba, size_t& bb, double dt, double sigma, std::vector<double>& tempsToadd, BlockManager& blockUser, std::vector<double>& SpecificBlockDists) {
	float EFF = sqrt(BlockA.physics.A * BlockB.physics.A);

	float distanceSquared = pow(BlockA.render.rect.x - BlockB.render.rect.x, 2) + pow(BlockA.render.rect.y - BlockB.render.rect.y, 2);
	SpecificBlockDists[bb] = (distanceSquared);

	float radiationCoefficient = sigma * BlockA.physics.emissivety *
		BlockB.physics.emissivety *
		EFF *
		(pow(BlockA.physics.temp, 4) - pow(BlockB.physics.temp, 4));


	if (distanceSquared < 1.0f){
		distanceSquared = 1.0f;
	}
	float radiationpower = radiationCoefficient / (distanceSquared);
	float Q = radiationpower * dt * 100;

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

void Physics::CheckOccultation(std::vector<ThermalBlocks>& Blocks, std::vector<double>& BlockDists, int i, std::vector<double>& tempsToadd, Cone& ConeHolder, bool& showShadow, int index) {
	bool Occulted = false;
	for (int j = 0; j < Blocks.size(); j++) {
		if (j == i) {
			continue;
		}
		
		for (int k = 0; k < Blocks.size(); k++) {
		
			if (k == j || k == i) {
				continue;
			}



			double BLOCK_I_CENTER[2] = { Blocks[i].render.rect.x + Blocks[i].render.rect.w / 2, Blocks[i].render.rect.y + Blocks[i].render.rect.h / 2 };
			double BLOCK_J_CENTER[2] = { Blocks[j].render.rect.x + Blocks[j].render.rect.w / 2, Blocks[j].render.rect.y + Blocks[j].render.rect.h / 2};
			double BLOCK_K_CENTER[2] = { Blocks[k].render.rect.x + Blocks[k].render.rect.w / 2, Blocks[k].render.rect.y + Blocks[k].render.rect.h / 2 };
			

			double dist_IJ = sqrt(BlockDists[j]);
			double dist_IK = std::hypot(BLOCK_K_CENTER[0] - BLOCK_I_CENTER[0],BLOCK_K_CENTER[1] - BLOCK_I_CENTER[1]);

			if (dist_IK >= dist_IJ || dist_IK == 0.0f) {
				continue;
			}

			double angle_IJ = atan2(BLOCK_J_CENTER[1] - BLOCK_I_CENTER[1], BLOCK_J_CENTER[0] - BLOCK_I_CENTER[0]) + std::numbers::pi;
			double angle_IK = atan2(BLOCK_K_CENTER[1] - BLOCK_I_CENTER[1], BLOCK_K_CENTER[0] - BLOCK_I_CENTER[0]) + std::numbers::pi;

			double angleRadius_J = asin(0.5 * Blocks[j].render.rect.w / dist_IJ);
			double angleRadius_K = asin(0.5 * Blocks[k].render.rect.w / dist_IK);

			Blocks[j].angle.interval[0] = angle_IJ - angleRadius_J;
			Blocks[j].angle.interval[1] = angle_IJ + angleRadius_J;

			double KLeft = angle_IK - angleRadius_K;
			double KRight = angle_IK + angleRadius_K;


			double overlapStart = std::max(Blocks[j].angle.interval[0], KLeft);
			double overlapEnd = std::min(Blocks[j].angle.interval[1], KRight);

			double BlockedFraction = 0;

			double overlapWidth = 0;

			if (overlapEnd >= overlapStart) {
				overlapWidth = overlapEnd - overlapStart;
			}
			else {
				continue;
			}

			double recieverWidth = abs(Blocks[j].angle.interval[1] - Blocks[j].angle.interval[0]);

			BlockedFraction = overlapWidth / recieverWidth;

			double VisibleFraction = 1 - BlockedFraction;


			tempsToadd[j] *= VisibleFraction;
			Occulted = true;

			if (showShadow && i == index) {

				double iCentreX = Blocks[i].render.rect.x + Blocks[i].render.rect.w / 2.0;
				double iCentreY = Blocks[i].render.rect.y + Blocks[i].render.rect.h / 2.0;

				double kCentreX = Blocks[k].render.rect.x + Blocks[k].render.rect.w / 2.0;
				double kCentreY = Blocks[k].render.rect.y + Blocks[k].render.rect.h / 2.0;

				double angleToK = atan2(
					kCentreY - iCentreY,
					kCentreX - iCentreX
				);

				double theta = angleToK;


				double dx = cos(theta);
				double dy = sin(theta);

				double halfW = Blocks[k].render.rect.w / 2.0;
				double halfH = Blocks[k].render.rect.h / 2.0;

				double tx = halfW / abs(dx);
				double ty = halfH / abs(dy);

				double t = std::min(tx, ty);

				double point2X = kCentreX - dx * t;
				double point2Y = kCentreY - dy * t;

				double px = -dy;
				double py = dx;

				ConeHolder.Angle = theta;

				double halfWidth = Blocks[k].render.rect.w / 2.0;

				ConeHolder.Lx = kCentreX - px * halfWidth;
				ConeHolder.Ly = kCentreY - py * halfWidth;

				ConeHolder.Rx = kCentreX + px * halfWidth;
				ConeHolder.Ry = kCentreY + py * halfWidth;
			}
		}

	}
	if (!Occulted) {
		ConeHolder.Angle = -1;
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

float Physics::setdt(std::vector<ThermalBlocks>& block, double sigma, BlockManager& blockUser) {
	ThermalBlocks Ba{}, Bb{};
	float MaxHeatA = 0;
	float MinHeatB = 2e4;
	for (auto& b : block) {
		if (b.physics.temp > MaxHeatA) {
			MaxHeatA = b.physics.temp;
			Ba = b;
		}
		if (b.physics.temp < MinHeatB){
			MinHeatB = b.physics.temp;
			Bb = b;
		}
	}


	float distSq = pow(Ba.render.rect.x - Bb.render.rect.x, 2) + pow(Ba.render.rect.y - Bb.render.rect.y, 2);
	float estRadPower = abs((sigma * Ba.physics.emissivety *
		Bb.physics.emissivety *
		sqrt(Ba.physics.A * Bb.physics.A) *
		(pow(Ba.physics.temp, 4) - pow(Bb.physics.temp, 4)))/distSq);

	float TempDif = blockUser.GetTempDif(Ba.physics.temp, Bb.physics.temp);

	float k = (Ba.physics.kC + Bb.physics.kC) / 2;
	float A = std::min(Ba.physics.A, Bb.physics.A);
	float d = (Ba.physics.d + Bb.physics.d) / 2;

	float estCondPower = abs((k * A * TempDif) / d);

	double old_temp = Ba.physics.temp;
	double space_temp = 2.7;

	double temp_fourthed = old_temp * old_temp * old_temp * old_temp;
	double space4 = space_temp * space_temp * space_temp * space_temp;

	double estDSCPower =
		std::abs(
			Ba.physics.emissivety *
			sigma *
			Ba.physics.A *
			(temp_fourthed - space4)
		);

	float usedPow = std::max(estCondPower, estRadPower);
	usedPow = std::max((double)usedPow, estDSCPower);

	int maxtemptransfer = 2;

	if (usedPow <= 0) {
		return 1.0f / 120.0f;
	}

	if (((maxtemptransfer*Ba.physics.mass * Ba.physics.specific_heat_energy) / usedPow) > (1.0f / 120.0f) or block.empty()) {
		return (1.0f/120.0f);
	}
	else {
		return (maxtemptransfer*Ba.physics.mass * Ba.physics.specific_heat_energy) / usedPow;
	}
}