#include "SDL_events.h"
#include "quee_sound.h"
#include <SDL.h>
#undef main

#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <stdbool.h>
#include <stdint.h>

#include "quee_helpers.h"
#include "quee_global_manager.h"
#include "quee_renderer.h"
#include "quee_scene.h"
#include "quee_sprite.h"
#include "quee_texture.h"
#include "quee_script.h"
#include "quee_entity.h"
#include "quee_input.h"

SDL_Renderer* g_renderer;
quee_global_manager* g_quee_manager;

int main(void) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO));

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0)
    );

    g_renderer =
        check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    g_quee_manager = create_quee_global_manager();

    check_quee_code(quee_load_sound(g_quee_manager->sound_manager, "assets/sounds/test.ogg"));

    quee_scene *scene = load_quee_scene("assets/scene.json");
    check_quee_code(quee_scene_manager_insert(
        g_quee_manager->scene_manager, scene));
    bool quit = false;

    uint32_t frame_start, frame_end, prev_frame_start;
    unsigned int delta_ticks = 0;
    float ms_elapsed;
    prev_frame_start = SDL_GetTicks();
    while(!quit) {
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
        frame_start = SDL_GetTicks();
        delta_ticks = frame_start - prev_frame_start;
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
                        case SDLK_SEMICOLON:
                            quee_toggle_debug_render();
                            break;
                    }
                    break;
            }
        }
        // Update scenes and do physics
        for(int i = 0; i < g_quee_manager->scene_manager->current_capacity; i++) {
            update_quee_scene(g_quee_manager->scene_manager->scenes[i], delta_ticks);
        }
         
        // Render all scenes 
        // The scenes will also tell if they want to be rendered
        SDL_RenderClear(g_renderer);
        for (int i = 0; i < g_quee_manager->scene_manager->current_capacity; i++) {
            check_quee_code(
                quee_render_scene(g_renderer, g_quee_manager->scene_manager->scenes[i])
            );
        }
        SDL_RenderPresent(g_renderer);
        
        //Save this frames input so that we can tell if we release keys
        update_quee_input(g_quee_manager->input_manager);

        frame_end = SDL_GetTicks();

        ms_elapsed = (frame_end - frame_start) / 1000.0f;

        /*printf("FPS: %2f Ticks: %f\n", 1000.0f / (TICKS_PER_FRAME - ms_elapsed), ms_elapsed);*/

        SDL_Delay(floor(TICKS_PER_FRAME - ms_elapsed));
        prev_frame_start = frame_start;
    }

    destroy_quee_global_manager(&g_quee_manager);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
