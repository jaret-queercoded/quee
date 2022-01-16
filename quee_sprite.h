#pragma once

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct quee_sprite quee_sprite;

struct quee_sprite {
    SDL_Texture *texture;
};

quee_sprite *create_quee_sprite_from_image_path(SDL_Renderer *renderer, const char *file);

void destroy_quee_sprite(quee_sprite *sprite);
