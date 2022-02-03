#ifndef QUEE_ENTITY_H_
#define QUEE_ENTITY_H_

#include "quee_sprite.h"

#define QUEE_SPRITE_BIT 0x01 

typedef struct quee_entity quee_entity;

struct quee_entity {
    unsigned int id;
    unsigned int type:1;
    quee_sprite *sprite; 
    quee_rect pos;
};

quee_entity * create_quee_entity();
void destroy_quee_entity(quee_entity **entity);
int add_to_quee_entity(quee_entity *entity, unsigned int type, void *ptr);
void update_quee_entity(quee_entity *entity, unsigned int delta_ticks);

#endif

