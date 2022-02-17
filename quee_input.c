#include "quee_input.h"
#include <stdlib.h>
#include <stdio.h>

quee_input_manager* create_quee_input_manager() {
    quee_input_manager* manager = malloc(sizeof(quee_input_manager));
    for(int i = 0; i < QUEE_NUMBER_OF_KEYS; i++) {
        manager->key_pressed[i] = false;
    }
    return manager;
}

void destroy_quee_input_manager(quee_input_manager **manager) {
    free(*manager);
    *manager = NULL;
}

//TODO pressing capslock and many other keys that arent letters
//causes a boundary error and crashes the program
void quee_input_pressed(quee_input_manager *manager, int code) {
    printf("Pressed key: %d\n", code);
    //TODO Temporary fix to stop crash
    if(code > 200) return;
    manager->key_pressed[code] = true;
}

void quee_input_released(quee_input_manager *manager, int code) {
    //TODO Temporary fix to stop crash
    if(code > 200) return;
    manager->key_pressed[code] = false;
}
