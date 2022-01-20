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
#include "quee_texture.h"
#include "quee_managers.h"

SDL_Renderer* g_renderer;
quee_managers* g_managers;

int main(void) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER));

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0)
    );

    g_renderer =
        check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);

    g_managers = create_quee_managers();
    check_quee_code(quee_scene_manager_insert(
        g_managers->scene_manager, load_quee_scene("assets/scene.json", g_renderer)));
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
        SDL_RenderClear(g_renderer);
        for (int i = 0; i < g_managers->scene_manager->current_capacity; i++) {
          check_quee_code(
              quee_render_scene(g_renderer, g_managers->scene_manager->scenes[i]));
        }
        SDL_RenderPresent(g_renderer);
        frame_end = SDL_GetTicks();

        ms_elapsed = (frame_end - frame_start) / 1000.0f;

//        printf("FPS: %2f\n", 1000.0f / (TICKS_PER_FRAME - ms_elapsed));

        SDL_Delay(floor(TICKS_PER_FRAME - ms_elapsed));
    }

    destroy_quee_managers(&g_managers);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);

    SDL_Quit();

    return 0;
}
