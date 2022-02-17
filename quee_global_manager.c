#include "quee_global_manager.h"
#include <stdlib.h>

quee_global_manager* create_quee_global_manager() {
    quee_global_manager *manager = malloc(sizeof(quee_global_manager));
    manager->texture_manager = create_quee_texture_manager(1);
    manager->scene_manager = create_quee_scene_manager(10);
    manager->script_manager = create_quee_script_manager();
    manager->input_manager = create_quee_input_manager();
    return manager;
}

void destroy_quee_global_manager(quee_global_manager **manager) {
    destroy_quee_scene_manager(&(*manager)->scene_manager);
    destroy_quee_texture_manager(&(*manager)->texture_manager);
    destroy_quee_script_manager(&(*manager)->script_manager);
    destroy_quee_input_manager(&(*manager)->input_manager);
    free(*manager);
    manager = NULL;
}
