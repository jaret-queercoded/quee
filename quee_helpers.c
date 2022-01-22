#include "quee_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL_error.h>
#include <string.h>

// Checks the sdl return code to see if something went wrong
// 
// If something went wrong we print the error and exit
void check_sdl_code(int code) {
    if(code < 0) {
        fprintf(stderr, "SDL encountered an error: %s\n", SDL_GetError());
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
        fprintf(stderr, "SDL gave you a null ptr: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static char quee_error_message[1024];

char* quee_get_error() {
    return quee_error_message;
}

void check_quee_code(int code) {
    if(code < 0) {
        fprintf(stderr, "Quee encountered an error: %s\n", quee_get_error());
        exit(EXIT_FAILURE);
    }
}

void* check_quee_ptr(void *ptr) {
    if(ptr == NULL) {
        fprintf(stderr, "Quee returned a null ptr: %s\n", quee_get_error());
        exit(EXIT_FAILURE);
    }
    return ptr;
}


void quee_set_error(char* format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(quee_error_message, format, args);
    va_end(args);
}

//djb2 hash function
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
