#ifndef QUEE_INPUT_H_
#define QUEE_INPUT_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct quee_input_manager quee_input_manager;

struct quee_input_manager { 
    const uint8_t *current_frame;
    uint8_t *previous_frame;
};

quee_input_manager* create_quee_input_manager();
void destroy_quee_input_manager(quee_input_manager **manager);
void update_quee_input(quee_input_manager *manager);

bool quee_input_is_held(quee_input_manager *manager, const char *key);
bool quee_input_is_pressed(quee_input_manager *manager, const char *key);
bool quee_input_was_released(quee_input_manager *manager, const char *key);

#endif

