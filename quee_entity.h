#ifndef QUEE_ENTITY_H_
#define QUEE_ENTITY_H_

#include "quee_sprite.h"
#include <uuid/uuid.h>

#define QUEE_SPRITE_BIT 0x01 

typedef struct quee_entity quee_entity;

struct quee_entity {
    unsigned int id;
    unsigned int type;
    quee_sprite *sprite; 
};

quee_entity * create_quee_entity();
void destroy_quee_entity(quee_entity **entity);
int add_to_quee_entity(quee_entity *entity, unsigned int type, void *ptr);

#endif
