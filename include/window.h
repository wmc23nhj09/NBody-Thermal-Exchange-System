#pragma once
#include <SDL3/SDL.h>

class Window {
public:
	Window();
	~Window();
	SDL_Window* window;
	SDL_Renderer* renderer;

	int WINDOW_W = 0;
	int WINDOW_H = 0;
};