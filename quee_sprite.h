#ifndef QUEE_SPRITE_H_
#define QUEE_SPRITE_H_

#include "quee_texture.h"
#include "quee_rect.h"

typedef struct quee_sprite quee_sprite;
typedef struct quee_frame quee_frame;

struct quee_sprite {
    quee_texture *texture;
    uint16_t max_frames;
    uint16_t num_frames;
    uint16_t frame_index;
    uint16_t ticks_on_frame;
    quee_frame *curr_frame;
    quee_frame **frames;
};

struct quee_frame {
    quee_rect rect;
    uint16_t ticks;
};

quee_sprite *create_quee_sprite(quee_texture *texture);
int quee_sprite_init_frames(quee_sprite *sprite, int number_of_frames);
int quee_sprite_add_frame(quee_sprite *sprite, quee_frame frame);

void destroy_quee_sprite(quee_sprite **sprite);

void update_quee_sprite(quee_sprite *sprite, unsigned int time_delta);


#endif

