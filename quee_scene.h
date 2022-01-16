#pragma once

#include <stdint.h>

typedef struct SDL_Renderer SDL_Renderer;

typedef struct quee_scene quee_scene;
typedef struct quee_sprite quee_sprite;

struct quee_scene {
    uint64_t n_sprites;
    quee_sprite** sprites;
};

quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer *renderer);

void destroy_quee_scene(quee_scene *scene);
