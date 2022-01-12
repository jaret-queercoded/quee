#include <stdio.h>
#include <stdlib.h>
#include <SDL_error.h>

// Checks the sdl return code to see if something went wrong
// 
// If something went wrong we print the error and exit
void check_sdl_code(int code) {
    if(code < 0) {
        fprintf(stderr, "SDL encountered an error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

// This function takes in void pointer that can be any sdl pointer and checks in
// in the event that something goes wrong we print the error and then quit
//
// If everything is good we then return the ptr so that it can be done inline with
// getting the pointer back from sdl and before assigning it to our var
// 
// Please don't give this a non sdl pointer because that would be mean :(
void* check_sdl_ptr(void *ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "SDL gave you a null ptr: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}
