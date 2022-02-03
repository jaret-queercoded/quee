#include "quee_sprite.h"
#include "quee_helpers.h"
#include "quee_texture.h"

#include <stdlib.h>


quee_sprite* create_quee_sprite(quee_texture *texture) {
    // Allocate memory for the sprite
    quee_sprite *sprite = malloc(sizeof(quee_sprite));

    // Assign texture for the sprite
    sprite->texture = texture;
    sprite->frames = NULL;
    sprite->curr_frame = NULL;
    sprite->max_frames = 0;
    sprite->num_frames = 0;
    sprite->frame_index = 0;
    sprite->ticks_on_frame = 0;
    
    return sprite;
}

int quee_sprite_init_frames(quee_sprite *sprite, int number_of_frames) {
    // Set some info for loading frames later
    sprite->max_frames = number_of_frames;
    // Allocate memory for the frames
    sprite->frames = malloc(sizeof(quee_frame *) * sprite->max_frames);
    for(int i = 0; i < sprite->max_frames; i++) {
        sprite->frames[i] = malloc(sizeof(quee_frame));
    }
    sprite->curr_frame = sprite->frames[0];
    return 0;
}


int quee_sprite_add_frame(quee_sprite *sprite, quee_frame frame) { 
    if(sprite->num_frames == sprite->max_frames) {
        quee_set_error("Exceeded max number of frames in sprite");
        return -1;
    }
    sprite->num_frames++;
    quee_frame *frame_ptr = sprite->frames[sprite->num_frames - 1];
    *frame_ptr = frame;
    return 0;
}

void destroy_quee_sprite(quee_sprite **sprite) {
    for(int i = 0; i < (*sprite)->max_frames; i++) {
        free((*sprite)->frames[i]);
    }
    free((*sprite)->frames);
    free(*sprite);
    *sprite = NULL;
}

void update_quee_sprite(quee_sprite *sprite, unsigned int time_delta) {
    sprite->ticks_on_frame += time_delta;
    if(sprite->ticks_on_frame >= sprite->curr_frame->ticks) {
        sprite->frame_index = ++sprite->frame_index % sprite->num_frames;
        sprite->curr_frame = sprite->frames[sprite->frame_index];
        sprite->ticks_on_frame = 0.0f;
    }
}
