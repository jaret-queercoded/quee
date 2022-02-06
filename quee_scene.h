#ifndef QUEE_SCENE_H_
#define QUEE_SCENE_H_

#include <stdint.h>
#include <stdbool.h>

#include "quee_helpers.h"

typedef struct SDL_Renderer SDL_Renderer;

typedef struct quee_scene quee_scene;
typedef struct quee_scene_manager quee_scene_manager;
typedef struct quee_entity quee_entity;
typedef struct quee_texture_manager quee_texture_manager;
typedef struct quee_script_manager quee_script_manager;

struct quee_scene_manager {
    quee_scene** scenes;
    uint64_t current_capacity;
    uint64_t max_capacity;
};

//TODO shift from a array base entity system to a parent child system
struct quee_scene {
    char name[MAX_STR_LEN];
    bool render;
    uint64_t max_entities;
    uint64_t current_entities;
    quee_entity** entities;
};

quee_scene_manager* create_quee_scene_manager(uint64_t capacity);
int quee_scene_manager_insert(quee_scene_manager *manager, quee_scene *scene);
int quee_scene_manager_remove(quee_scene_manager *manager, char *scene_name);
void destroy_quee_scene_manager(quee_scene_manager **manager);

quee_scene* create_quee_scene();
quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer *renderer, quee_texture_manager *texture_manager, quee_script_manager *script_manager);
int quee_scene_add_entity(quee_scene *scene, quee_entity *entity);
void update_quee_scene(quee_scene *scene, unsigned int delta_ticks);

void destroy_quee_scene(quee_scene **scene);

#endif
