#include "window.h"

Window::Window() {
	SDL_CreateWindowAndRenderer(
		"NBody Conductive And Radioactive Thermal Exchange",
		WINDOW_W,
		WINDOW_H,
		SDL_WINDOW_BORDERLESS,
		&window,
		&renderer);
}


Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}