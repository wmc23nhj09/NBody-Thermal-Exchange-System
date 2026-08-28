#include <imgui.h>
#include "UI.h"
#include <SDL3/SDL.h>
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

void UI::SetFlags(ImGuiWindowFlags& window_flags) {
	window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;      // Removes the top title bar
	window_flags |= ImGuiWindowFlags_NoResize;        // Disables dragging the edges
	window_flags |= ImGuiWindowFlags_NoMove;          // Disables moving the window
	window_flags |= ImGuiWindowFlags_NoCollapse;      // Disables the minimize button
	window_flags |= ImGuiWindowFlags_NoBackground;    // Makes the gray background transparent
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus; // Keeps your game blocks interactive
};

void UI::DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags window_flags, float& CreationTemp, float& CreationMass, float& CreationEmissivety, float& CreationSpecificHeatEnergy, float& CreationDensity, float& CreationKC, bool& DSC, bool& Radiation, bool& Conduction) {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);


	ImGui::Begin("My Window", nullptr, window_flags);

	// ---------- REAL UI BEGIN ----------
	//EMISSIVETY SLIDER
	ImGui::SetCursorPos(ImVec2(40, 718));
	ImGui::PushItemWidth(300);
	ImGui::SliderFloat("Emissivety", &CreationEmissivety, 0.001f, 1);

	//MASS SLIDER
	ImGui::PushItemWidth(630);
	ImGui::SetCursorPos(ImVec2(550, 718));
	ImGui::SliderFloat("Mass", &CreationMass, 0.001f, 100);

	//DENSITY SLIDER
	ImGui::PushItemWidth(450);
	ImGui::SetCursorPos(ImVec2(40, 818));
	ImGui::SliderFloat("Density", &CreationDensity, 0.001f, 100.0f);

	//KC SLIDER
	ImGui::PushItemWidth(630);
	ImGui::SetCursorPos(ImVec2(600, 818));
	ImGui::SliderFloat("Thermal Conductivity", &CreationKC, 0.001f, 1000);

	//SPECIFIC HEAT ENERGY SLIDER
	ImGui::PushItemWidth(1278-40);
	ImGui::SetCursorPos(ImVec2(40, 908));
	ImGui::SliderFloat("Specific Heat Energy", &CreationSpecificHeatEnergy, 0.001f, 1000);
	ImGui::PopItemWidth();

	//TEMP SLIDE
	ImGui::SetCursorPos(ImVec2(40, 1000));
	ImGui::SliderFloat("Initial Temperature", &CreationTemp, 1, 20000);

	//DSC Button
	ImGui::SetCursorPos(ImVec2(1600, 50));
	
	ImGui::Checkbox("Deep Space Cooling", &DSC);

	ImGui::SetCursorPos(ImVec2(1600, 200));

	ImGui::Checkbox("Radiation", &Radiation);

	ImGui::SetCursorPos(ImVec2(1600, 350));

	ImGui::Checkbox("Conduction", &Conduction);

	// ---------- REAL UI END ----------
	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}