#include <stdio.h>
#include <string.h>

#include "quee_scene_test.h"

#define NUMBER_OF_TESTS 5 

typedef struct quee_test quee_test;

struct quee_test {
    void (*func_ptr)();
    char *suite;
};

quee_test tests[NUMBER_OF_TESTS] = {
    {.func_ptr = test_quee_scene_manager_creation, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_manager_add_scene, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_manager_remove_scene, .suite = "quee_scene_manager"},
    {.func_ptr = test_quee_scene_creation, .suite = "quee_scene"},
    {.func_ptr = test_quee_load_scene, .suite = "quee_scene"},
};

int main(int argc, char** argv) {
    if(argc == 1) {
        for(int i = 0; i < NUMBER_OF_TESTS; i++) {
            printf("Running test [%d/%d]: ", i + 1, NUMBER_OF_TESTS);
            tests[i].func_ptr();
        }
    }
    // Selective Test Running
    else {
        quee_test filtered_tests[NUMBER_OF_TESTS];
        int x = 0;
        for(int i = 1; i < argc; i++) {
            char* target = argv[i];
            for(int j = 0; j < NUMBER_OF_TESTS; j++) {
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
