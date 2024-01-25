#pragma once
#include "matrix.h"
#include <iostream>
#include <SDL.h>
#include <stdint.h>

class Window {
public:
	Window(const char* title, int width, int height, int pixelSize);
	~Window();

	void clear();
	void present();
	void setPixel(int x, int y, int color);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;
	SDL_Texture* m_tex;
	Matrix<uint32_t>* m_pixels;
	int m_width;
	int m_height;
	int m_pixelSize;
};