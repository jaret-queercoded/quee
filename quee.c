#include <SDL.h>

#include <stdbool.h>

#include "quee_helpers.h"

int main(void) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO));
    SDL_Window *window = check_sdl_ptr(SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0));
    
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

    return 0;
}
