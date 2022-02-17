#ifndef QUEE_INPUT_H_
#define QUEE_INPUT_H_

#include <stdbool.h>

typedef struct quee_input_manager quee_input_manager;

#define QUEE_NUMBER_OF_KEYS 200 

//TODO expand this to have more information than if the key is pressed
//I want to be able to tell if the key was just released
//I also want the ability to remap keys from the engine
//Perhpas just monitoring a few user defined keys
struct quee_input_manager { 
    bool key_pressed[QUEE_NUMBER_OF_KEYS];
};

quee_input_manager* create_quee_input_manager();
void destroy_quee_input_manager(quee_input_manager **manager);

void quee_input_pressed(quee_input_manager *manager, int code);
void quee_input_released(quee_input_manager *manager, int code);

#endif

