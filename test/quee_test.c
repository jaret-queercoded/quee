#include <stdio.h>
#include <string.h>

#include "quee_scene_test.h"

typedef struct quee_test quee_test;

struct quee_test {
    void (*func_ptr)();
    char *suite;
};

quee_test tests[] = {
    {.func_ptr = test_quee_scene_manager_creation, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_manager_add_scene, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_manager_remove_scene, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_creation, .suite = "quee_scene"},
    {.func_ptr = test_quee_load_scene, .suite = "quee_scene"},
};

//We use a global render pointer in c so I just make a null one here for tests
typedef struct SDL_Renderer SDL_Renderer;
SDL_Renderer *g_renderer = NULL;

int main(int argc, char** argv) {
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
    return 0;
}
