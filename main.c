#include <SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    bool quit = false;
    while(!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
}
