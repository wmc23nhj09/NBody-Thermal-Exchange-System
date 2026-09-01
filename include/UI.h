#pragma once
#include <SDL3/SDL.h>
#include "imgui.h"

class UI {
public:
	void SetFlags(ImGuiWindowFlags& window_flags);
	void DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags window_flags, float& CreationTemp, float& CreationMass, float& CreationEmissivety, float& CreationSpecificHeatEnergy, float& CreationDensity, float& CreationKC, bool& DSC, bool& Radiation, bool& Conduction, const int& WINHEIGHT, const int& WINWIDTH);
};