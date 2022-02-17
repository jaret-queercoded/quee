#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#undef main

#include "quee_test_helper.h"
#include "quee_scene_test.h"
#include "quee_texture_test.h"
#include "quee_sprite_test.h"
#include "quee_script_test.h"

#include "../quee_helpers.h"

typedef struct quee_test quee_test;

struct quee_test {
    quee_test_result (*func_ptr)();
    char *suite;
};

quee_test tests[] = {
    {.func_ptr = test_quee_scene_manager_creation, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_manager_add_scene, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_manager_remove_scene, .suite = QUEE_SCENE_MANAGER_SUITE},
    {.func_ptr = test_quee_scene_creation, .suite = QUEE_SCENE_SUITE},
    {.func_ptr = test_quee_load_scene, .suite = QUEE_SCENE_SUITE},
    {.func_ptr = test_quee_texture_creation_and_deletion, .suite = QUEE_TEXTURE_SUITE},
    {.func_ptr = test_quee_texture_manager_creation_and_deletion, .suite = QUEE_TEXTURE_MANAGER_SUITE},
    {.func_ptr = test_quee_get_texture, .suite = QUEE_TEXTURE_MANAGER_SUITE},
    {.func_ptr = test_quee_remove_texture, .suite = QUEE_TEXTURE_MANAGER_SUITE},
    {.func_ptr = test_quee_sprite_creation, .suite = QUEE_SPRITE_SUITE},
    {.func_ptr = test_quee_sprite_add_frame, .suite = QUEE_SPRITE_SUITE},
    {.func_ptr = test_quee_sprite_update, .suite = QUEE_SPRITE_SUITE},
    {.func_ptr = test_quee_script_creation, .suite = QUEE_SCRIPT_SUITE},
    {.func_ptr = test_quee_script_function_type, .suite = QUEE_SCRIPT_SUITE},
    {.func_ptr = test_quee_script_run_function, .suite = QUEE_SCRIPT_SUITE},
};

//We use a global render pointer in c so I just make a null one here for tests
typedef struct SDL_Renderer SDL_Renderer;
SDL_Renderer *g_renderer = NULL;
typedef struct quee_global_manager quee_global_manager;
quee_global_manager *g_quee_manager = NULL;

int main(int argc, char** argv) {
    // setup sdl for tests that need it
    check_sdl_code(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = check_sdl_ptr(
        SDL_CreateWindow("quee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIDDEN)
    );

    g_renderer =
        check_sdl_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    // Figure out how many tests are in the array of tests
    int num_tests = sizeof(tests) / sizeof(quee_test);

    // Array to save failures
    quee_test_result failures[100];
    int num_failures = 0;
    if(argc == 1) {
        for(int i = 0; i < num_tests; i++) {
            printf("Running test [%d/%d]: ", i + 1, num_tests);
            quee_test_result test_result = tests[i].func_ptr();
            if(test_result.result) {
                printf("%s PASSED!\n", test_result.name);
            }
            else {
                printf("%s FAILED!\n", test_result.name);
                failures[num_failures++] = test_result;
            }
        }
    }
    // Selective Test Running
    else {
        quee_test filtered_tests[100];
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
            quee_test_result test_result = filtered_tests[i].func_ptr();
            if(test_result.result) {
                printf("%s PASSED!\n", test_result.name);
            }
            else {
                printf("%s FAILED!\n", test_result.name);
                failures[num_failures++] = test_result;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(g_renderer);
    SDL_Quit();

    if(num_failures) {
        printf("\n\nFAILURES:\n");
        for(int i = 0; i < num_failures; i++) {
            quee_test_result test_result = failures[i];
            printf("%s failed with error: %s at %s:%d\n", test_result.name, test_result.msg, test_result.file, test_result.line); 
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
