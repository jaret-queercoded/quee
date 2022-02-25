#include "quee_collider.h"
#include "quee_entity.h"

#include <stdlib.h>
#include <stdio.h>

quee_box_collider* create_quee_box_collider(quee_vec2i size, uint8_t mask) {
    quee_box_collider *box = malloc(sizeof(quee_box_collider));
    box->size = size;
    box->collision_mask = mask;
    return box;
}

void destroy_quee_box_collider(quee_box_collider **collider) {
    free(*collider);
    *collider = NULL;
}

bool quee_check_collision(quee_entity *e1, quee_entity *e2) {
    if(e1->box_collider == NULL || e2->box_collider == NULL) {
        return false;
    }
    double e1re = e1->pos.x + e1->box_collider->size.x;
    double e1le = e1->pos.x;
    double e1te = e1->pos.y;
    double e1be = e1->pos.y + e1->box_collider->size.y;
    double e2re = e2->pos.x + e2->box_collider->size.x;
    double e2le = e2->pos.x;
    double e2te = e2->pos.y;
    double e2be = e2->pos.y + e2->box_collider->size.y;
    printf("e1: %f, %f, %f, %f\n", e1le, e1re, e1te, e1be);
    printf("e2: %f, %f, %f, %f\n", e2le, e2re, e2te, e2be);
    if(e1re <= e2le &&
        e1le >= e2re) {
        printf("Collision: %f,%f %f,%f\n", e1->pos.x, e1->pos.y, e2->pos.x, e2->pos.y);
        return true;
    }
    return false;
}
