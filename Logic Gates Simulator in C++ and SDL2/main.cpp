#include <iostream>
#include <SDL.h>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
int SQUARE_SIZE = 50;

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL Init error: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Logic Gate Simulator in C++ and SDL2",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "SDL Window error: " << SDL_GetError() << "\n";
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cerr << "SDL Renderer error: " << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Rect square = {
		(WINDOW_WIDTH - SQUARE_SIZE) / 2,
		(WINDOW_HEIGHT - SQUARE_SIZE) / 2,
		SQUARE_SIZE,
		SQUARE_SIZE
	};

	bool running = true;
	bool dragging = false;
	SDL_Point mousePoint;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					mousePoint.x = event.button.x;
					mousePoint.y = event.button.y;
					if (SDL_PointInRect(&mousePoint, &square)) {
						dragging = true;
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {
					dragging = false;
				}
				break;

			case SDL_MOUSEMOTION:
				if (dragging) {
					int dx = event.motion.xrel;
					int dy = event.motion.yrel;
					square.x += dx;
					square.y += dy;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &square);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;

}