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

void UI::DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags window_flags, float& CreationTemp, float& CreationMass, float& CreationEmissivety, float& CreationSpecificHeatEnergy, float& CreationDensity, float& CreationKC, bool& DSC, bool& Radiation, bool& Conduction, const int& WINHEIGHT, const int& WINWIDTH) {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);


	ImGui::Begin("My Window", nullptr, window_flags);

	// ---------- REAL UI BEGIN ----------
	//EMISSIVETY SLIDER
	ImGui::SetCursorPos(ImVec2(0.02*WINWIDTH, 0.67*WINHEIGHT));
	ImGui::PushItemWidth(0.16*WINWIDTH);
	ImGui::SliderFloat("Emissivety", &CreationEmissivety, 0.001f, 1);

	//MASS SLIDER
	ImGui::PushItemWidth(0.33*WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.28*WINWIDTH, 0.67*WINHEIGHT));
	ImGui::SliderFloat("Mass", &CreationMass, 1, 100);

	//DENSITY SLIDER
	ImGui::PushItemWidth(0.24*WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.02*WINWIDTH, 0.77*WINHEIGHT));
	ImGui::SliderFloat("Density", &CreationDensity, 1, 100.0f);

	//KC SLIDER
	ImGui::PushItemWidth(0.33*WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.31*WINWIDTH, 0.77*WINHEIGHT));
	ImGui::SliderFloat("Thermal Conductivity", &CreationKC, 0.001f, 1000);

	//SPECIFIC HEAT ENERGY SLIDER
	ImGui::PushItemWidth(0.64*WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.02*WINWIDTH, 0.85*WINHEIGHT));
	ImGui::SliderFloat("Specific Heat Energy", &CreationSpecificHeatEnergy, 1, 1000);
	ImGui::PopItemWidth();

	//TEMP SLIDE
	ImGui::SetCursorPos(ImVec2(0.02*WINWIDTH, 0.94*WINHEIGHT));
	ImGui::SliderFloat("Initial Temperature", &CreationTemp, 1, 20000);

	//DSC Button
	ImGui::SetCursorPos(ImVec2(0.84*WINWIDTH, 0.06*WINHEIGHT));
	
	ImGui::Checkbox("Deep Space Cooling", &DSC);

	ImGui::SetCursorPos(ImVec2(0.84 * WINWIDTH, 0.2*WINHEIGHT));

	ImGui::Checkbox("Radiation", &Radiation);

	ImGui::SetCursorPos(ImVec2(0.84 * WINWIDTH, 0.33*WINHEIGHT));

	ImGui::Checkbox("Conduction", &Conduction);

	ImGui::SetCursorPos(ImVec2(0.67 * (float)WINWIDTH, 0.65 * (float)WINHEIGHT));
<<<<<<< HEAD
	ImGui::Text("Hello Nikky");
=======
	//ImGui::Text("Hello Nikky");
>>>>>>> origin/master

	// ---------- REAL UI END ----------
	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}