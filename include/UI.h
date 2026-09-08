#pragma once
#include <SDL3/SDL.h>
#include "imgui.h"
#include "blocks.h"

class UI {
public:
	void SetFlags(ImGuiWindowFlags& window_flags);
	//void Property(const char* name, const char* value);
	void DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags window_flags, float& CreationTemp, float& CreationMass, float& CreationEmissivety, float& CreationSpecificHeatEnergy, float& CreationDensity, float& CreationKC, bool& DSC, bool& Radiation, bool& Conduction, const int& WINHEIGHT, const int& WINWIDTH, std::vector<ThermalBlocks*> block);
};