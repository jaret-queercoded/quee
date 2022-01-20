#ifndef QUEE_SPRITE_H_
#define QUEE_SPRITE_H_

#include "quee_texture.h"

typedef struct quee_sprite quee_sprite;

struct quee_sprite {
    quee_texture *texture;
};

quee_sprite *create_quee_sprite(quee_texture *texture);

void destroy_quee_sprite(quee_sprite **sprite);

#endif

