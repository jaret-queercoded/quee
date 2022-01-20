#ifndef QUEE_SCENE_H_
#define QUEE_SCENE_H_

#include <stdint.h>
#include <stdbool.h>

#include "quee_helpers.h"

typedef struct SDL_Renderer SDL_Renderer;

typedef struct quee_scene quee_scene;
typedef struct quee_scene_manager quee_scene_manager;
typedef struct quee_sprite quee_sprite;
typedef struct quee_texture_manager quee_texture_manager;

struct quee_scene_manager {
    quee_scene** scenes;
    uint64_t current_capacity;
    uint64_t max_capacity;
};

struct quee_scene {
    char name[MAX_STR_LEN];
    bool render;
    uint64_t max_sprites;
    uint64_t current_sprites;
    quee_sprite** sprites;
};

quee_scene_manager* create_quee_scene_manager(uint64_t capacity);
int quee_scene_manager_insert(quee_scene_manager *manager, quee_scene *scene);
int quee_scene_manager_remove(quee_scene_manager *manager, char *scene_name);
void destroy_quee_scene_manager(quee_scene_manager **manager);

quee_scene* create_quee_scene();
quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer *renderer, quee_texture_manager *texture_manager);
int quee_scene_add_sprite(quee_scene *scene, quee_sprite *sprite);

void destroy_quee_scene(quee_scene **scene);

#endif
