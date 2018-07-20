#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* stretched = NULL;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	} else {
		win = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (win == NULL) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		} else {
			screen = SDL_GetWindowSurface(win);
		}
	}
	
	return true;
}

// Load image at specified path as SDL_Surface*
SDL_Surface* loadsurface(char* path)
{
	SDL_Surface* img = SDL_LoadBMP(path);
	
	if (img == NULL) {
		printf("Unable to load image! SDL error: %s\n", SDL_GetError());
	}
	
	return img;
}

bool loadmedia()
{
	stretched = loadsurface("stretch.bmp");
	if (stretched == NULL) {
		printf("Failed to load default image!\n");
		return false;
	}
	
	return true;
}

void closegame()
{
	SDL_FreeSurface(stretched);
	stretched = NULL;
	
	SDL_DestroyWindow(win);
	win = NULL;
	
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
				
				SDL_Rect rect;
				rect.x = 0;
				rect.y = 0;
				rect.w = SCREEN_WIDTH;
				rect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(stretched, NULL, screen, &rect);
				SDL_UpdateWindowSurface(win);
			}
		}
	}
	
	closegame();
	return 0;
}