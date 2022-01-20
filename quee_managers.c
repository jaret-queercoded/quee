#include "quee_managers.h"
#include "quee_scene.h"
#include "quee_texture.h"

#include <stdlib.h>

quee_managers* create_quee_managers() {
    quee_managers *managers = malloc(sizeof(quee_managers));
    managers->scene_manager = create_quee_scene_manager(BASE_CAPACITY);
    managers->texture_manager = create_quee_texture_manager(BASE_CAPACITY);
    return managers;
}

void destroy_quee_managers(quee_managers **managers) {
    destroy_quee_scene_manager(&(*managers)->scene_manager);
    destroy_quee_texture_manager(&(*managers)->texture_manager);
    free(*managers);
    *managers = NULL;
}
