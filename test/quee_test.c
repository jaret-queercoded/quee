#include <stdio.h>

#include "quee_scene_test.h"

#define NUMBER_OF_TESTS 2

void (*tests[NUMBER_OF_TESTS]) () = {test_scene_manager_creation, failure};

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;
    printf("Running quee tests!\n");
    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        printf("Running test %d of %d\n", i + 1, NUMBER_OF_TESTS);
        fflush(stdout);
        tests[i]();
    }
    printf("Test Completed Succesfully!\n");
    return 0;
}
