#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (gWindow == NULL) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    
    return true;
}

bool loadMedia()
{
    gHelloWorld = IMG_Load("/Users/nsm/Desktop/TestSDL/TestSDL/santa.jpg");
    
    if (gHelloWorld == NULL) {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

void shutDown()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    if (!init()) {
        printf("Failed to initialize");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media");
        } else {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
        }
    }
    
    shutDown();
    return 0;
}