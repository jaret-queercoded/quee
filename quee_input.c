#include "quee_input.h"

#include "SDL_keyboard.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

quee_input_manager* create_quee_input_manager() {
    quee_input_manager* manager = malloc(sizeof(quee_input_manager));
    manager->current_frame = SDL_GetKeyboardState(NULL);
    manager->previous_frame = malloc(sizeof(uint8_t) * 512);
    memset(manager->previous_frame, 0, 512);
    return manager;
}

void destroy_quee_input_manager(quee_input_manager **manager) {
    free((*manager)->previous_frame);
    free(*manager);
    *manager = NULL;
}

void update_quee_input(quee_input_manager *manager) {
    memcpy(manager->previous_frame, manager->current_frame, 512);
}

bool quee_input_is_held(quee_input_manager *manager, const char *key) {
    SDL_Scancode code = SDL_GetScancodeFromName(key);
    //We couldn't get the code
    if(code == 0) {
        fprintf(stderr, "Something went wrong getting scan code for: %s\nError: %s\nPress enter to quit...\n", key, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return manager->current_frame[code];
}

bool quee_input_is_pressed(quee_input_manager *manager, const char *key) {
    SDL_Scancode code = SDL_GetScancodeFromName(key);
    //We couldn't get the code
    if(code == 0) {
        fprintf(stderr, "Something went wrong getting scan code for: %s\nError: %s\nPress enter to quit...\n", key, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return manager->current_frame[code] && !manager->previous_frame[code];
}

bool quee_input_was_released(quee_input_manager *manager, const char *key) {
    SDL_Scancode code = SDL_GetScancodeFromName(key);
    //We couldn't get the code
    if(code == 0) {
        fprintf(stderr, "Something went wrong getting scan code for: %s\nError: %s\nPress enter to quit...\n", key, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //If the key is not pressed this frame and it was last then we had to have released
    return !manager->current_frame[code] && manager->previous_frame[code];
}
