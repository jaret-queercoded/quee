#ifndef QUEE_SPRITE_H_
#define QUEE_SPRITE_H_

#include "quee_texture.h"
#include "quee_math.h"

typedef struct quee_sprite quee_sprite;

struct quee_sprite {
    quee_texture *texture;
    uint16_t frame_count;
    uint16_t curr_frame;
    uint16_t ticks_per_frame;
    uint16_t ticks_on_frame;
    vec2i frame_size;
    vec2i pos;
};

quee_sprite *create_quee_sprite(quee_texture *texture, vec2i size, vec2i pos);

void destroy_quee_sprite(quee_sprite **sprite);

void update_quee_sprite(quee_sprite *sprite, unsigned int time_delta);

#endif

