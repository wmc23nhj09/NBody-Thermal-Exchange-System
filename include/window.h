#pragma once
#include <SDL3/SDL.h>

class Window {
public:
	Window();
	~Window();
	SDL_Window* window;
	SDL_Renderer* renderer;

	const int WINDOW_W = 800;
	const int WINDOW_H = 800;
};