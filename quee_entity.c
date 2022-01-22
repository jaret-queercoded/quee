#include "quee_entity.h"

#include <stdlib.h>

#include "quee_helpers.h"
#include "quee_sprite.h"

quee_entity * create_quee_entity() {
    quee_entity *entity = malloc(sizeof(quee_entity));
    entity->type = 0;
    entity->sprite = NULL;
    return entity;
}

void destroy_quee_entity(quee_entity **entity) {
    if((*entity)->type & QUEE_SPRITE_BIT) {
        destroy_quee_sprite(&(*entity)->sprite);
    }
    free(*entity);
    entity = NULL;
}

int add_to_quee_entity(quee_entity *entity, unsigned int type, void *ptr) {
    if(entity->type & type) {
        quee_set_error("quee_entity already has a field of that type");
        return -1;
    }
    switch (type) {
        case QUEE_SPRITE_BIT:
            entity->sprite = ptr;
            break;
        default:
            quee_set_error("quee_entity doesn't support that type");
            return -1;
    } 
    entity->type &= type;
    return 0;
}
