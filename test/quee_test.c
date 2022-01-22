#include <stdio.h>
#include <string.h>

#include <SDL.h>

#include "quee_scene_test.h"
#include "quee_texture_test.h"

#include "../quee_helpers.h"

typedef struct quee_test quee_test;

struct quee_test {
    void (*func_ptr)();
    char *suite;
};

quee_test tests[] = {
    {.func_ptr = test_quee_scene_manager_creation, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_manager_add_scene, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_manager_remove_scene, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_creation, .suite = QUEE_SCENE_SUITE},
    {.func_ptr = test_quee_load_scene, .suite = QUEE_SCENE_SUITE},
    {.func_ptr = test_quee_texture_creation_and_deletion, .suite = QUEE_TEXTURE_SUITE},
};

//We use a global render pointer in c so I just make a null one here for tests
typedef struct SDL_Renderer SDL_Renderer;
SDL_Renderer *g_renderer = NULL;

int main(int argc, char** argv) {
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIDDEN)
    );

    g_renderer =
        check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    // Figure out how many tests are in the array of tests
    int num_tests = sizeof(tests) / sizeof(quee_test);
    if(argc == 1) {
        for(int i = 0; i < num_tests; i++) {
            printf("Running test [%d/%d]: ", i + 1, num_tests);
            tests[i].func_ptr();
        }
    }
    // Selective Test Running
    else {
        quee_test filtered_tests[num_tests];
        int x = 0;
        for(int i = 1; i < argc; i++) {
            char* target = argv[i];
            for(int j = 0; j < num_tests; j++) {
                if(strcmp(target, tests[j].suite) == 0) {
                    filtered_tests[x++] = tests[j];
                }
            }
        }

        for(int i = 0; i < x; i++) {
            printf("Running filtered test [%d/%d]: ", i + 1, x);
            filtered_tests[i].func_ptr();
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();

    return 0;
}
