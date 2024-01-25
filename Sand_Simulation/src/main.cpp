#include "window.h"
#include <iostream>
#include <SDL.h>
#include <timer.h>

const int WIDTH = 50;
const int HEIGHT = 75;
const int PIXEL_SIZE = 12;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int DRAW_COLOR = 0xF2D2A9;

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing SDL2 - Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	Matrix<int> sand = Matrix<int>(WIDTH, HEIGHT, 0);

	Window window = Window("Sand Simulation", WIDTH, HEIGHT, PIXEL_SIZE);

	SDL_Event event;

	bool mouseDown = false;

	bool running = true;

	LTimer fpsTimer;

	LTimer capTimer;

	int countedFrames = 0;
	fpsTimer.start();


	while (running) {
		capTimer.start();

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseDown = true;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseDown = false;
				break;

			case SDL_MOUSEMOTION:
				if (mouseDown) {
					int x = (event.motion.x / PIXEL_SIZE);
					int y = (event.motion.y / PIXEL_SIZE);

					if (x >= 0 and x <= WIDTH - 1) {
						if (y >= 0 and x <= HEIGHT - 1) {
							sand.set(x, y, 1);
						}
					}
				}
				break;
			}
		}

		for (int y = HEIGHT; y > 0; y--) {
			for (int x = 0; x < WIDTH; x++) {
				if (sand.get(x, y) == 1) {
					window.setPixel(x, y, DRAW_COLOR);
					if (sand.get(x, y + 1) == 0 && (y + 1) < HEIGHT) {
						sand.set(x, y, 0);
						sand.set(x, y + 1, 1);
					}
				}
				else {
					window.setPixel(x, y, 0xFFFFFF);
				}
			}
		}
		
		window.clear();
		window.present();

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	return 0;
}