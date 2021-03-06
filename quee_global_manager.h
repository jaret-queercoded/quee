#ifndef QUEE_GLOBAL_MANAGER_H_
#define QUEE_GLOBAL_MANAGER_H_

#include "quee_texture.h"
#include "quee_scene.h"
#include "quee_script.h"
#include "quee_input.h"
#include "quee_sound.h"
#include "quee_thread.h"

typedef struct quee_global_manager quee_global_manager;

struct quee_global_manager {
    quee_texture_manager *texture_manager;
    quee_scene_manager *scene_manager;
    quee_script_manager *script_manager;
    quee_input_manager *input_manager;
    quee_sound_manager *sound_manager;
    quee_thread_pool *thread_pool;
};

quee_global_manager* create_quee_global_manager();
void destroy_quee_global_manager(quee_global_manager **manager);

#endif

