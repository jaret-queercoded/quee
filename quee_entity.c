#include "quee_entity.h"

#include <stdlib.h>
#include <uuid/uuid.h>

#include "quee_helpers.h"
#include "quee_sprite.h"

//TODO Figure out a better way to ids
static unsigned int NEXT_ID = 0;

/**
 * @brief Create an empty entity
 *
 * @return An empty entity that you then add compnents to 
 */
quee_entity * create_quee_entity() {
    quee_entity *entity = malloc(sizeof(quee_entity));
    entity->type = 0;
    entity->sprite = NULL;
    entity->id = NEXT_ID++;
    return entity;
}

/**
 * @brief Destroys a given entity
 *
 * @param entity Entity to be destoryed
 */
void destroy_quee_entity(quee_entity **entity) {
    if((*entity)->type & QUEE_SPRITE_BIT) {
        destroy_quee_sprite(&(*entity)->sprite);
    }
    free(*entity);
    entity = NULL;
}

/**
 * @brief Add a compnent to the entity
 *
 * @param entity Entity to add to 
 * @param type Bit field corresponding to what is being added
 * @param ptr Pointer to what we want added
 *
 * @return -1 on failure and 0 on success 
 */
int add_to_quee_entity(quee_entity *entity, unsigned int type, void *ptr) {
    if(entity->type & type) {
        quee_set_error("quee_entity already has a field of that type: 0x%04x", type);
        return -1;
    }
    switch (type) {
        case QUEE_SPRITE_BIT:
            entity->sprite = ptr;
            break;
        default:
            quee_set_error("quee_entity doesn't support that type: 0x%04x", type);
            return -1;
    } 
    entity->type |= type;
    return 0;
}
