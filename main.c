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
#include "quee_script.h"
#include "quee_entity.h"

SDL_Renderer* g_renderer;

int main(void) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER));

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0)
    );

    g_renderer =
        check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);

    quee_texture_manager *texture_manager = create_quee_texture_manager(1);
    quee_scene_manager *scene_manager = create_quee_scene_manager(10);
    quee_script_manager *script_manager = create_quee_script_manager(10);

    check_quee_code(quee_scene_manager_insert(
        scene_manager, load_quee_scene("assets/scene.json", g_renderer, texture_manager, script_manager)));
    bool quit = false;

    uint32_t frame_start, frame_end, prev_frame_start;
    unsigned int delta_ticks = 0.0f;
    float ms_elapsed;
    prev_frame_start = SDL_GetTicks();
    while(!quit) {
        frame_start = SDL_GetTicks();
        delta_ticks = frame_start - prev_frame_start;
        /*printf("delta_ticks: %d\n", delta_ticks);*/
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
            }
        }
        // Update scenes and do physics
        for(int i = 0; i < scene_manager->current_capacity; i++) {
            update_quee_scene(scene_manager->scenes[i], delta_ticks);
        }
         
        // Render all scenes 
        // The scenes will also tell if they want to be rendered
        SDL_RenderClear(g_renderer);
        for (int i = 0; i < scene_manager->current_capacity; i++) {
            check_quee_code(
                quee_render_scene(g_renderer, scene_manager->scenes[i])
            );
        }
        SDL_RenderPresent(g_renderer);
        frame_end = SDL_GetTicks();

        ms_elapsed = (frame_end - frame_start) / 1000.0f;


        /*printf("FPS: %2f Ticks: %f\n", 1000.0f / (TICKS_PER_FRAME - ms_elapsed), ms_elapsed);*/

        SDL_Delay(floor(TICKS_PER_FRAME - ms_elapsed));
        prev_frame_start = frame_start;
    }

    destroy_quee_scene_manager(&scene_manager);
    destroy_quee_texture_manager(&texture_manager);
    destroy_quee_script_manager(&script_manager);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);

    SDL_Quit();

    return 0;
}
