#ifndef QUEE_ENTITY_H_
#define QUEE_ENTITY_H_

#include "quee_sprite.h"
#include "quee_script.h"

#define QUEE_SPRITE_BIT 0x01 
#define QUEE_SCRIPT_BIT 0x02

typedef struct quee_entity quee_entity;

//TODO switch to an parent child based entity system instead of
//an array based system that we currently have I believe that 
//this will make it much easier to traverse the entity for locating
//other entities to use them in scripts and what not
struct quee_entity {
    unsigned int id;
    unsigned int type:2;
    char *name;
    quee_sprite *sprite; 
    quee_script *script;
    quee_rect pos;
};

quee_entity * create_quee_entity();
void destroy_quee_entity(quee_entity **entity);
int add_to_quee_entity(quee_entity *entity, unsigned int type, void *ptr);
void update_quee_entity(quee_entity *entity, unsigned int delta_ticks);

#endif

