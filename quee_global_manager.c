#include "quee_global_manager.h"
#include "quee_sound.h"
#include "quee_thread.h"
#include <stdlib.h>

quee_global_manager* create_quee_global_manager() {
    quee_global_manager *manager = malloc(sizeof(quee_global_manager));
    manager->texture_manager = create_quee_texture_manager(10);
    manager->scene_manager = create_quee_scene_manager(10);
    manager->script_manager = create_quee_script_manager();
    manager->input_manager = create_quee_input_manager();
    manager->sound_manager = create_quee_sound_manager(10);
    manager->thread_pool = create_quee_thread_pool(10);
    return manager;
}

void destroy_quee_global_manager(quee_global_manager **manager) {
    destroy_quee_scene_manager(&(*manager)->scene_manager);
    destroy_quee_texture_manager(&(*manager)->texture_manager);
    destroy_quee_script_manager(&(*manager)->script_manager);
    destroy_quee_input_manager(&(*manager)->input_manager);
    destroy_quee_sound_manager(&(*manager)->sound_manager);
    destroy_quee_thread_pool(&(*manager)->thread_pool);
    free(*manager);
    manager = NULL;
}
