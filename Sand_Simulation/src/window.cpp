#include "matrix.h"
#include "window.h"
#include <iostream>
#include <SDL.h>
#include <stdint.h>

Window::Window(const char* title, int width, int height, int pixelSize)
:m_width(width), m_height(height), m_pixelSize(pixelSize) {
	SDL_Window* window = NULL;
	window = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_width * m_pixelSize,
		m_height * m_pixelSize,
		0
	);

	if (!window) {
		std::cout << "Failed to create window\n";
	}

	m_window = window;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	m_tex = SDL_CreateTexture(
		m_renderer,
		SDL_PIXELFORMAT_XRGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		m_width,
		m_height
	);

	m_pixels = new Matrix<uint32_t>(m_width, m_height, 255);
	SDL_UpdateTexture(m_tex, NULL, m_pixels->raw(), m_width * sizeof(Uint32));
}

Window::~Window() {
	SDL_DestroyWindow(m_window);
	delete m_pixels;
}

void Window::clear() {
	SDL_SetRenderDrawColor(m_renderer, 100, 100, 200, 100);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_tex, NULL, NULL);
}

void Window::present() {
	SDL_RenderPresent(m_renderer);
}

void Window::setPixel(int x, int y, int color) {
	m_pixels->set(x, y, color);
	
	SDL_UpdateTexture(m_tex, NULL, m_pixels->raw(), m_width * sizeof(Uint32));
}