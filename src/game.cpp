#include "SDL3/SDL.h"
#include "game.h"
#include "blocks.h"
#include "physics.h"
#include "imgui.h"
#include "iostream"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"
#include "renderer.h"
#include "UI.h"
//MAX TEMP : 1.89 x 10 ^ 9

float temptry = 20000;
//Main Game Class
	//Initliasation when Class runs (__init__) --> In CPP it is referred to as a CONSTRUCTOR CLASS
Game::Game() : running(true),
window(),
renderer(window.renderer),
//PHYSICS							 //RENDERING											 //INTERACTION
//Temp      A   D   Mass, E  SHE   K  KC||        RECT						 RGB				 || Held   Down
blocksinuse({ { {1,   1, 25, 1, 1, 900, 0.0f, 400}, {{10, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false}},
			{   {temptry,     1, 25, 1, 1, 500, 0.0f, 400}, { {50, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} },
			{   {temptry,    1, 25, 1, 1, 300, 0.0f, 400}, { {90, 10, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} },
			{   {1,       1, 25, 1, 1, 500, 0.0f, 400},{ {30, 50, 20, 20}, {(Uint32)0, (Uint32)0, (Uint32)0}}, {false, false} } }),
	tempsToadd{},
	distanceoffsetx(-1.0f),
	distanceoffsety(-1.0f),
	e{},
	blockrender(),
	physicswork(),
	Ui(),
	mouse({ 0,0,1,1 }),
	mouseMap(),
	dt(),
	SimSpeed(100.0f),
	Simdt(),
	sigma(5.67e-8),
	emissivety(1),
	transferspeed(100.0f),
	framesbefore(),
	framesnow(),
	CreationTemp(1),
	CreationMass(1),
	CreationEmissivety(0.001f),
	CreationSpecificHeatEnergy(0.001f),
	CreationDensity(1),
	CreationKC(0.001f),
	Create(false),
	Destroy(false),
	DSC(true),
	Radiation(true),
	Conduction(true)
{
};

//Main Game Loop
void Game::run() {
	ImGuiWindowFlags window_flags = 0;

	ImGui::CreateContext();
	ImGui_ImplSDL3_InitForSDLRenderer(window.window, renderer.renderer);
	ImGui_ImplSDLRenderer3_Init(renderer.renderer);

	//framesbefore = SDL_GetPerformanceCounter();
	while (running) {
		//framesnow = SDL_GetPerformanceCounter();

		//dt = ((float)(framesnow - framesbefore) / SDL_GetPerformanceFrequency()) / 1200.0f;
		dt = physicswork.setdt(blocksinuse, sigma, blockrender);

		Simdt = dt * SimSpeed;
		framesbefore = framesnow;
		mouseMap = SDL_GetMouseState(&mouse.x, &mouse.y);
		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL3_ProcessEvent(&e);

			if ((e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) || e.type == SDL_EVENT_QUIT) {
				running = false;
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_R) {
				blocksinuse.clear();
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				for (auto& b : blocksinuse) {
					blockrender.getHeldState(mouse, &b);
				}

				if (!(mouse.x > 1258) && !(mouse.y > 697)) {

					if (Create) {
						if (blocksinuse.size() > 0) {
							for (auto& b : blocksinuse) {
								if (b.interaction.held) {
									break;
								}
								else {
									SDL_FRect tempRect = { mouse.x, mouse.y, 20, 20 };
									blocksinuse.push_back(blockrender.CreateBlock(CreationTemp, tempRect, 1, CreationDensity, CreationMass, CreationEmissivety, CreationSpecificHeatEnergy, CreationKC));
								}
							}
						}
						else {
							SDL_FRect tempRect = { mouse.x, mouse.y, 20, 20 };
							blocksinuse.push_back(blockrender.CreateBlock(CreationTemp, tempRect, 1, CreationDensity, CreationMass, CreationEmissivety, CreationSpecificHeatEnergy, CreationKC));
						}
					}
					else if (Destroy) {
						for (auto it = blocksinuse.begin(); it != blocksinuse.end(); ) {
							if (it->interaction.held) {
								it = blocksinuse.erase(it);
							}
							else {
								++it;
							}
						}
					}
				}
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				for (auto& b : blocksinuse) {
					b.interaction.held = false;
				}
				distanceoffsetx = -1.0f;
				distanceoffsety = -1.0f;
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_Q) {
				Create = !Create;

				if (Destroy) {
					Destroy = false;
				}
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_E) {
				Destroy = !Destroy;

				if (Create) {
					Create = false;
				}
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_F) {
				Create = false;
				Destroy = false;
			}
		}
		for (auto& b : blocksinuse) {
			blockrender.moveBlocks(&b, mouse, distanceoffsetx, distanceoffsety);
		}
		physicsbackground();
		renderer.update(blocksinuse, mouse, blockrender, Create, Destroy);
		Ui.SetFlags(window_flags);
		Ui.DrawUI(renderer.renderer, window_flags, CreationTemp, CreationMass, CreationEmissivety, CreationSpecificHeatEnergy, CreationDensity, CreationKC, DSC, Radiation, Conduction);
		SDL_RenderPresent(renderer.renderer);
	}
};

void Game::physicsbackground() {

	physicswork.getCoolingConstant(sigma, blocksinuse);
	if (DSC) {
		physicswork.DeepSpaceHeatTransfer(&blocksinuse, dt, transferspeed, sigma, emissivety);
	}

	float beforeenergy = 0;
	float afterenergy = 0;
	tempsToadd.assign(blocksinuse.size(), 0.0f);

	//std::cout << blocksinuse.size() << '\n';
	for (size_t i = 0; i < blocksinuse.size(); i++) {
		beforeenergy += (blocksinuse[i].physics.specific_heat_energy * blocksinuse[i].physics.mass * blocksinuse[i].physics.temp);
	}

	for (size_t i = 0; i < blocksinuse.size(); i++) {
		if (blocksinuse[i].render.rect.x + 20 > 1278) {
			blocksinuse[i].render.rect.x = 1258;
		}
		else if (blocksinuse[i].render.rect.x < 0) {
			blocksinuse[i].render.rect.x = 0;
		}
		if (blocksinuse[i].render.rect.y + 20 > 717) {
			blocksinuse[i].render.rect.y = 697;
		}
		else if (blocksinuse[i].render.rect.y < 0) {
			blocksinuse[i].render.rect.y = 0;
		}

		for (size_t j = i + 1; j < blocksinuse.size(); j++) {
			if (blockrender.getTouchingIndexes(blocksinuse[i], blocksinuse[j]) && Conduction) {
				physicswork.AddConduction(blocksinuse[i], blocksinuse[j], i, j, dt, transferspeed, tempsToadd, blockrender);
			}
			else if (Radiation) {
				physicswork.AddRadiation(blocksinuse[i], blocksinuse[j], i, j, dt, transferspeed, sigma, tempsToadd, blockrender);
			}
		}
	}

	for (size_t i = 0; i < tempsToadd.size(); i++) {
		blocksinuse[i].physics.temp += tempsToadd[i];
		physicswork.GetRGB(&blocksinuse[i]);
	}
	

	for (size_t i = 0; i < blocksinuse.size(); i++) {
		afterenergy += (blocksinuse[i].physics.specific_heat_energy * blocksinuse[i].physics.mass * blocksinuse[i].physics.temp);
	}

}