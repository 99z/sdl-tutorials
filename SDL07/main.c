#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Window to render to
SDL_Window* win = NULL;

// Renderer represents current rendering state
SDL_Renderer* renderer = NULL;

// Texture being displayed
SDL_Texture* tex = NULL;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	} else {
		// Enable linear texture filtering, handle if we couldn't
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: linear texture filtering not enabled");
		}

		win = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (win == NULL) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return false;
		} else {
			// -1 initializes the first rendering driver with available flags
			renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Renderer could not be created! %s\n", SDL_GetError());
				return false;
			} else {
				// Controls what color is used for various rendering operations
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0XFF);

				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
					printf("SDL_image could not initialize! %s\n", IMG_GetError());
					return false;
				}
			}
		}
	}
	
	return true;
}

SDL_Texture* loadtexture(char* path)
{
	SDL_Texture* tex = NULL;
	SDL_Surface* surf = IMG_Load(path);
	
	if (surf == NULL) {
		printf("Failed to load image as surface! %s\n", SDL_GetError());
	} else {
		tex = SDL_CreateTextureFromSurface(renderer, surf);

		if (tex == NULL) {
			printf("Failed to create texture! %s\n", SDL_GetError());
		}

		SDL_FreeSurface(surf);
	}

	return tex;
}

bool loadmedia()
{
	tex = loadtexture("texture.png");
	if (tex == NULL) {
		printf("Failed to load default image!\n");
		return false;
	}
	
	return true;
}

void closegame()
{
	SDL_DestroyTexture(tex);
	tex = NULL;
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	renderer = NULL;
	win = NULL;
	
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if (!init()) {
		printf("Failed to initialize");
	} else {
		if (!loadmedia()) {
			printf("Failed to load media");
		} else {
			bool quit = false;
			SDL_Event e;
						
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, tex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
	}
	
	closegame();
	return 0;
}