#include "window.h"

Window::Window() {
	SDL_CreateWindowAndRenderer(
		"M.O.R.E. Model - Multi-Object Radiation Exchange",
		WINDOW_W,
		WINDOW_H,
		SDL_WINDOW_RESIZABLE,
		&window,
		&renderer);
}


Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}