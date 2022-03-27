#include "quee_entity.h"

#include <stdlib.h>
#include <stdio.h>

#include "quee_collider.h"
#include "quee_helpers.h"
#include "quee_sprite.h"
#include "quee_script.h"

//TODO Figure out a better way to ids
static unsigned int NEXT_ID = 0;

/**
 * @brief Create an empty entity
 *
 * @return An empty entity that you then add compnents to 
 */
quee_entity* create_quee_entity(quee_scene *scene) {
    quee_entity *entity = malloc(sizeof(quee_entity));
    entity->type = 0;
    entity->scene = scene;
    entity->name = NULL;
    entity->sprite = NULL;
    entity->script = NULL;
    entity->box_collider = NULL;
    entity->pos.x = 0.0;
    entity->pos.y = 0.0;
    entity->size.x = 0;
    entity->size.y = 0;
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
    if((*entity)->type & QUEE_SCRIPT_BIT) {
        destroy_quee_script(&(*entity)->script);
    }
    if((*entity)->type & QUEE_BOX_COLLIDER_BIT) {
        destroy_quee_box_collider(&(*entity)->box_collider);
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
        case QUEE_SCRIPT_BIT:
            entity->script = ptr;
            break;
        case QUEE_BOX_COLLIDER_BIT:
            entity->box_collider = ptr;
            break;
        default:
            quee_set_error("quee_entity doesn't support that type: 0x%04x", type);
            return -1;
    } 
    entity->type |= type;
    return 0;
}

void update_quee_entity(quee_entity *entity, unsigned int delta_ticks) {
    if(entity->type & QUEE_SCRIPT_BIT) {
        if(entity->script->type & QUEE_ON_UDPATE_BIT) {
            check_quee_code(run_quee_script_function(entity->script, "onUpdate", NULL));
        }
    }
    if(entity->type & QUEE_SPRITE_BIT) {
        update_quee_sprite(entity->sprite, delta_ticks);
    }
    if(entity->type & QUEE_BOX_COLLIDER_BIT) {
        entity->box_collider->colliding = false;
        for(int i = 0; i < entity->scene->current_entities; i++) {
            quee_entity *e = entity->scene->entities[i];
            if(e == NULL) continue;
            if(entity != e) {
                if(quee_check_collision(entity, e)) {
                    if(entity->type & QUEE_SCRIPT_BIT && entity->script->type & QUEE_ON_COLLIDE_BIT) {
                        check_quee_code(run_quee_script_function(entity->script, "onCollision", e));
                    }
                }
            }
        }
    }
}
