#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct SDL_Renderer SDL_Renderer;

typedef struct quee_scene quee_scene;
typedef struct quee_scene_manager quee_scene_manager;
typedef struct quee_sprite quee_sprite;

struct quee_scene_manager {
    quee_scene** scenes;
    uint32_t current_capacity;
    uint32_t max_capacity;
};

struct quee_scene {
    const char* name;
    bool render;
    uint64_t n_sprites;
    quee_sprite** sprites;
};

quee_scene_manager* create_quee_scene_manager(uint64_t capacity);
int quee_scene_manager_insert(quee_scene_manager *manager, quee_scene *scene);
int quee_scene_manager_remove_index(quee_scene_manager *manager, uint32_t index);
void destroy_quee_scene_manager(quee_scene_manager **manager);

quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer *renderer);

void destroy_quee_scene(quee_scene **scene);
