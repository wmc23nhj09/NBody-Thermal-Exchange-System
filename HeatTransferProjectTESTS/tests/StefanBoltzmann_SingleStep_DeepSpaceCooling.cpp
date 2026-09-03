#include "physics.h"
#include "blocks.h"
#include <iostream>
#include <vector>

void SB_DSP_Run() {
	std::vector<double> initialtemp = {100, 450, 900};
	float sigma = 5.670374419e-8;
	Physics physics;
	int SimSpeed = 100;
	float transferspeed = 1;
	float dt = 1;

	double ExpectedTempChange;
	double ActualTempChange;
	int count = 0;

	double errorPercentage;

	float acceptableErrorMargin = 1.0f;

	for (auto& temps : initialtemp) {
		std::vector<ThermalBlocks> blocksinuse{ { {temps, 1, 1, 10, 1, 900, 0.0f}, { {10, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} } };

		physics.getCoolingConstant(sigma, blocksinuse);
		for (auto& b : blocksinuse) {
			ExpectedTempChange = (((1 * sigma * pow(temps, 4)) * dt) / (10 * 900));
			physics.DeepSpaceHeatTransfer(&blocksinuse, dt, transferspeed, sigma, b.physics.emissivety);
			ActualTempChange = temps - b.physics.temp;
		}

		errorPercentage = fabs(100 - ((ActualTempChange / ExpectedTempChange) * 100));

		std::cout << "========================= Stefan-Boltzmann Deep Space Cooling Test (" << temps << "K) ======================== = \n";
		std::cout << "Initial Temperature:             " << temps << " K\n";
		std::cout << "Expected Temperature Drop:       " << ExpectedTempChange << " K\n";
		std::cout << "Acceptable Error:                " << acceptableErrorMargin << "% \n";
		std::cout << "Actual Temperature Drop:         " << ActualTempChange << " K\n";
		std::cout << "Error:                           " << errorPercentage << "% \n";

		if (errorPercentage < acceptableErrorMargin) {
			std::cout << "Pass\n";
			count++;
		}
		else {
			std::cout << "Fail";
		}
	}
	if (count == 3) {
		std::cout << "Stefan-Boltzmann equation implementation verified.";
	}
}