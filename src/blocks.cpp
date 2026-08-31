#include "SDL3/SDL.h"
#include "blocks.h"
#include "algorithm"
#include "windows.h"
#include "iostream"
#include "vector"


//Find the temperature difference between two objects
float BlockManager::GetTempDif(double Tempa, double Tempb) {
	if (Tempa > Tempb) {
		return Tempa - Tempb;
	}
	else {
		return Tempb - Tempa;
	}
}

//Create a block - MUST FIX
ThermalBlocks BlockManager::CreateBlock(double temp, SDL_FRect& rect, double A, double d, double mass, double emissivety, double specific_heat_energy, double k) {
	ThermalBlocks block = { {temp, A, d, mass, emissivety, specific_heat_energy, k}, { rect, {0, 0, 0}}, {false, false} };
	return block;
}

//Render all Blocks
void BlockManager::renderallblocks(ThermalBlocks& BlockManager, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, BlockManager.render.rgb.r, BlockManager.render.rgb.g, BlockManager.render.rgb.b, 0);
	SDL_RenderFillRect(renderer, &BlockManager.render.rect);
};

//Check if a block is being held
void BlockManager::getHeldState(SDL_FRect& mouse, ThermalBlocks* BlockManager) {
	if (mouse.x < BlockManager->render.rect.x + BlockManager->render.rect.w && mouse.x + mouse.w > BlockManager->render.rect.x && mouse.y < BlockManager->render.rect.y + BlockManager->render.rect.h && mouse.y + mouse.h > BlockManager->render.rect.y) {
		BlockManager->interaction.held = true;
	}
	else {
		BlockManager->interaction.held = false;
	}
}

//Check if two Block touch
bool BlockManager::getTouchingIndexes(ThermalBlocks& blocka, ThermalBlocks& blockb) {
	if (blocka.render.rect.x <= blockb.render.rect.x + blockb.render.rect.w && blocka.render.rect.x + blocka.render.rect.w >= blockb.render.rect.x && blocka.render.rect.y <= blockb.render.rect.y + blockb.render.rect.h && blocka.render.rect.y + blocka.render.rect.h >= blockb.render.rect.y) {
		return true;
	}
	return false;
}

//Move a block if it is held
void BlockManager::moveBlocks(ThermalBlocks* BlockManager, SDL_FRect& mouse, float& distanceoffsetx, float& distanceoffsety) {
	if (BlockManager->interaction.held) {
		if (distanceoffsetx == -1.0f) {
			distanceoffsetx = mouse.x - BlockManager->render.rect.x;
		}
		if (distanceoffsety == -1.0f) {
			distanceoffsety = mouse.y - BlockManager->render.rect.y;
		}
		BlockManager->render.rect.x = mouse.x - (distanceoffsetx);
		BlockManager->render.rect.y = mouse.y - (distanceoffsety);
	}
};

