#ifndef QUEE_COLLIDER_H_
#define QUEE_COLLIDER_H_

#include <stdint.h>
#include <stdbool.h>

#include "quee_rect.h"

typedef struct quee_box_collider quee_box_collider;
typedef struct quee_entity quee_entity;

struct quee_box_collider {
    quee_vec2i size;
    uint8_t collision_mask;
    bool colliding;
};

quee_box_collider* create_quee_box_collider(quee_vec2i size, uint8_t mask);
void destroy_quee_box_collider(quee_box_collider **collider);
bool quee_check_collision(quee_entity *, quee_entity *);

#endif

