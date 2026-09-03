#include <iostream>
#include <iomanip>
#include <algorithm>
#include "physics.h"
#include "blocks.h"

void MORE_EC_Run()
{
    std::vector<ThermalBlocks> blocksinuse({
        {{1200,1,25,1,5,900,0.0f}, {{10,10,20,20},{0,0,0}}, {false,false}},
        {{500, 1,25,1,2,500,0.0f}, {{50,10,20,20},{0,0,0}}, {false,false}},
        {{100, 1,25,1,3,700,0.0f}, {{30,50,20,20},{0,0,0}}, {false,false}}
        });

    Physics physics;
    BlockManager blockrender;

    float dt = 1.0f/1200.0f;
    float transferspeed = 1e3;
    float sigma = 5.670374419e-8f;

    // ---------- Initial energy ----------
    double beforeenergy = 0.0;
    for (auto& b : blocksinuse)
    {
        beforeenergy +=
            (double)b.physics.specific_heat_energy *
            (double)b.physics.mass *
            (double)b.physics.temp;
    }

    // ---------- Run until equilibrium ----------
    const float equilibriumTolerance = 0.05f;
    bool equilibriumReached = false;
    float ActualEquilibrium = 0.0f;
    int steps = 0;
    const int maxSteps = 1000000;

    float totalHeatCapacity = 0.0f;
    float weightedTemperature = 0.0f;


    for (auto& block : blocksinuse) {
        float heatCapacity = block.physics.mass * block.physics.specific_heat_energy;

        totalHeatCapacity += heatCapacity;
        weightedTemperature += heatCapacity * block.physics.temp;
    }

    float expectedEquilibrium = weightedTemperature / totalHeatCapacity;

    while (!equilibriumReached && steps < maxSteps)
    {
        std::vector<double> tempsToadd(blocksinuse.size(), 0.0f);

        // Calculate all pair interactions
        for (size_t i = 0; i < blocksinuse.size(); ++i)
        {
            for (size_t j = i + 1; j < blocksinuse.size(); ++j)
            {
                physics.AddRadiation(
                    blocksinuse[i],
                    blocksinuse[j],
                    i,
                    j,
                    dt,
                    transferspeed,
                    sigma,
                    tempsToadd,
                    blockrender);
            }
        }

        // Apply all temperature changes simultaneously
        for (size_t i = 0; i < blocksinuse.size(); ++i)
        {
            blocksinuse[i].physics.temp += tempsToadd[i];
        }

        // Check equilibrium
        double minT = blocksinuse[blocksinuse.size()-1].physics.temp;
        double maxT = blocksinuse[0].physics.temp;

        for (auto& b : blocksinuse)
        {
            minT = std::min(minT, b.physics.temp);
            maxT = std::max(maxT, b.physics.temp);
        }

        float totalTemperatureChange = 0.0f;

        for (auto& delta : tempsToadd)
        {
            totalTemperatureChange += fabs(delta);
        }

        float maxTemperatureDifference = abs(maxT - minT);
        //std::cout << maxTemperatureDifference << '\n';
        equilibriumReached = maxTemperatureDifference < 0.00001f && totalTemperatureChange < 0.0001f;
        ++steps;
    }


    // ---------- Final energy ----------
    double afterenergy = 0.0;
    for (auto& b : blocksinuse)
    {
        afterenergy +=
            (double)b.physics.specific_heat_energy *
            (double)b.physics.mass *
            (double)b.physics.temp;
    }

    double energyDifference = afterenergy - beforeenergy;
    double percentageError =
        (std::abs(energyDifference) / beforeenergy) * 100.0;

    std::cout << std::fixed << std::setprecision(10);

    std::cout << "========================= M-O_R_E Energy Conservation Test =========================\n";
    std::cout << "Steps to equilibrium: " << steps << "\n\n";

    for (size_t i = 0; i < blocksinuse.size(); ++i)
    {
        std::cout << "Object " << i
            << " Final Temp: "
            << blocksinuse[i].physics.temp << " K\n";
    }

    std::cout << "\nInitial Energy: " << beforeenergy << " J\n";
    std::cout << "Final Energy:   " << afterenergy << " J\n";
    std::cout << "Difference:     " << energyDifference << " J\n";
    std::cout << "Error:          " << percentageError << " %\n";

    std::cout << "Expected Equilibrium: " << expectedEquilibrium << " K\n";
    std::cout << "Actual Equilibrium: " << blocksinuse[0].physics.temp << " K\n";
    std::cout << "Difference:         " << fabs(expectedEquilibrium - blocksinuse[0].physics.temp) << " K\n";

    if (percentageError < 0.001f) {
        if (fabs(expectedEquilibrium - blocksinuse[0].physics.temp) < equilibriumTolerance) {
            std::cout << "Pass\n";
        }
        else {
            std::cout << "Fail - Equilibrium\n";
        }
    }
    else {
        if (fabs(blocksinuse[0].physics.temp - expectedEquilibrium) < equilibriumTolerance) {
            std::cout << "Fail - Conservation\n";
        }
        else {
            std::cout << "Fail\n";
        }
    }

}