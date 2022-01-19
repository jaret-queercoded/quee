#include <SDL.h>
#undef main

#include <SDL_render.h>
#include <SDL_timer.h>

#include <stdbool.h>
#include <stdint.h>

#include "quee_helpers.h"
#include "quee_renderer.h"
#include "quee_scene.h"
#include "quee_sprite.h"


int main(void) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER));

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0)
    );

    SDL_Renderer *renderer = check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    quee_scene_manager *manager = create_quee_scene_manager(10);
    check_quee_code(quee_scene_manager_insert(manager, load_quee_scene("assets/scene.json", renderer))); 
    bool quit = false;

    uint32_t frame_start, frame_end;
    float ms_elapsed;
    while(!quit) {
        frame_start = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        
        // Render all scenes 
        // The scenes will also tell if they want to be rendered
        SDL_RenderClear(renderer);
        for(int i = 0; i < manager->current_capacity; i++) {
            check_quee_code(quee_render_scene(renderer, manager->scenes[i]));
        }
        SDL_RenderPresent(renderer);
        frame_end = SDL_GetTicks();

        ms_elapsed = (frame_end - frame_start) / 1000.0f;

//        printf("FPS: %2f\n", 1000.0f / (TICKS_PER_FRAME - ms_elapsed));

        SDL_Delay(floor(TICKS_PER_FRAME - ms_elapsed));
    }

    destroy_quee_scene_manager(&manager);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    return 0;
}
