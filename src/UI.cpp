#include <imgui.h>
#include "UI.h"
#include "blocks.h"
#include "string"
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
	window_flags |= ImGuiSliderFlags_NoInput;		  // Stops Tab / Ctrl+Click abuse on sliders
};

void Property(const char* name, const char* value) {
	ImGui::TableNextRow();
	
	ImGui::TableNextColumn();
	ImGui::Text("%s", name);

	ImGui::TableNextColumn();
	ImGui::Text("%s", value);
}

void UI::DrawUI(SDL_Renderer* renderer, ImGuiWindowFlags window_flags, float& CreationTemp, float& CreationMass, float& CreationEmissivety, float& CreationSpecificHeatEnergy, float& CreationDensity, float& CreationKC, bool& DSC, bool& Radiation, bool& Conduction, const int& WINHEIGHT, const int& WINWIDTH, std::vector<ThermalBlocks*> block) {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);


	ImGui::Begin("My Window", nullptr, window_flags);

	// ---------- REAL UI BEGIN ----------
	//EMISSIVETY SLIDER
	ImGui::SetCursorPos(ImVec2(0.02 * WINWIDTH, 0.67 * WINHEIGHT));
	ImGui::PushItemWidth(0.16 * WINWIDTH);
	ImGui::SliderFloat("Emissivety", &CreationEmissivety, 0.1f, 1, "%.1f", ImGuiSliderFlags_NoInput);

	//MASS SLIDER
	ImGui::PushItemWidth(0.33 * WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.28 * WINWIDTH, 0.67 * WINHEIGHT));
	ImGui::SliderFloat("Mass", &CreationMass, 1, 100, "%.2f Kg", ImGuiSliderFlags_NoInput);

	//DENSITY SLIDER
	ImGui::PushItemWidth(0.24 * WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.02 * WINWIDTH, 0.77 * WINHEIGHT));
	ImGui::SliderFloat("Density", &CreationDensity, 1, 100.0f, "%.2f Kg/m3", ImGuiSliderFlags_NoInput);

	//KC SLIDER
	ImGui::PushItemWidth(0.33 * WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.31 * WINWIDTH, 0.77 * WINHEIGHT));
	ImGui::SliderFloat("Thermal Conductivity", &CreationKC, 0.001f, 1000, "%.4f W/(mK)", ImGuiSliderFlags_NoInput);

	//SPECIFIC HEAT ENERGY SLIDER
	ImGui::PushItemWidth(0.64 * WINWIDTH);
	ImGui::SetCursorPos(ImVec2(0.02 * WINWIDTH, 0.85 * WINHEIGHT));
	ImGui::SliderFloat("Specific Heat Energy", &CreationSpecificHeatEnergy, 1, 1000, "%.4f J/(KgK)", ImGuiSliderFlags_NoInput);
	ImGui::PopItemWidth();

	//TEMP SLIDE
	ImGui::SetCursorPos(ImVec2(0.02 * WINWIDTH, 0.94 * WINHEIGHT));
	ImGui::SliderFloat("Initial Temperature", &CreationTemp, 1, 20000, "%.3f K", ImGuiSliderFlags_NoInput);

	//DSC Button
	ImGui::SetCursorPos(ImVec2(0.84 * WINWIDTH, 0.06 * WINHEIGHT));

	ImGui::Checkbox("Deep Space Cooling", &DSC);

	ImGui::SetCursorPos(ImVec2(0.84 * WINWIDTH, 0.2 * WINHEIGHT));

	ImGui::Checkbox("Radiation", &Radiation);

	ImGui::SetCursorPos(ImVec2(0.84 * WINWIDTH, 0.33 * WINHEIGHT));

	ImGui::Checkbox("Conduction", &Conduction);

	ImGui::SetCursorPos(ImVec2(0.78 * WINWIDTH, 0.66 * WINHEIGHT));

	if (block[0] != nullptr && ImGui::BeginTable("Properties Block 1", 2)) {

		ImGui::TableSetupColumn("Property");
		ImGui::TableSetupColumn("Value");

		Property("Temp: ", std::to_string(block[0]->physics.temp).c_str());
		Property("Mass: ", std::to_string(block[0]->physics.mass).c_str());
		Property("Specific Heat Energy: ", std::to_string(block[0]->physics.specific_heat_energy).c_str());
		Property("Emissivity: ", std::to_string(block[0]->physics.emissivety).c_str());
		Property("Area: ", std::to_string(block[0]->physics.A).c_str());
		Property("Density: ", std::to_string(block[0]->physics.d).c_str());
		Property("Thermal Conductivity: ", std::to_string(block[0]->physics.kC).c_str());
		//ImGui::Text(("Cooling Constant: " + std::to_string(block->physics.k)).c_str());
		ImGui::EndTable();
	}

	ImGui::SetCursorPos(ImVec2(0.78 * WINWIDTH, 0.79 * WINHEIGHT));
	if (block[1] != nullptr && ImGui::BeginTable("Properties Block 2", 2)) {

		ImGui::TableSetupColumn("Property");
		ImGui::TableSetupColumn("Value");

		Property("Temp: ", std::to_string(block[1]->physics.temp).c_str());
		Property("Mass: ", std::to_string(block[1]->physics.mass).c_str());
		Property("Specific Heat Energy: ", std::to_string(block[1]->physics.specific_heat_energy).c_str());
		Property("Emissivity: ", std::to_string(block[1]->physics.emissivety).c_str());
		Property("Area: ", std::to_string(block[1]->physics.A).c_str());
		Property("Density: ", std::to_string(block[1]->physics.d).c_str());
		Property("Thermal Conductivity: ", std::to_string(block[1]->physics.kC).c_str());
		//ImGui::Text(("Cooling Constant: " + std::to_string(block->physics.k)).c_str());
		ImGui::EndTable();
	}
	// ---------- REAL UI END ----------
	ImGui::End();

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}
