#include "quee_sprite.h"
#include "quee_helpers.h"
#include "quee_texture.h"

#include <stdlib.h>


quee_sprite* create_quee_sprite(quee_texture *texture, vec2i frame_size, vec2i pos) {
    // Allocate memory for the sprite
    quee_sprite *sprite = malloc(sizeof(quee_sprite));

    // Assign texture for the sprite
    sprite->texture = texture;
    sprite->frame_size = frame_size;
    sprite->pos = pos;
    // TODO Implement setting frame info somewhere else probably in scene loading
    // and pass these values in
    sprite->frame_count = 2;
    sprite->curr_frame = 0;
    sprite->ticks_per_frame = 1000;
    sprite->ticks_on_frame = 0;
    return sprite;
}

void destroy_quee_sprite(quee_sprite **sprite) {
    free(*sprite);
    *sprite = NULL;
}

void update_quee_sprite(quee_sprite *sprite, unsigned int time_delta) {
    sprite->ticks_on_frame += time_delta;
    if(sprite->ticks_on_frame >= sprite->ticks_per_frame) {
        sprite->curr_frame = ++sprite->curr_frame % sprite->frame_count;
        sprite->ticks_on_frame = 0.0f;
    }
}
