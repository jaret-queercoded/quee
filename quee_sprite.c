#include "quee_sprite.h"
#include "quee_helpers.h"
#include "quee_texture.h"

#include <stdlib.h>


quee_sprite* create_quee_sprite(quee_texture *texture) {
    // Allocate memory for the sprite
    quee_sprite *sprite = malloc(sizeof(quee_sprite));

    // Assign texture for the sprite
    sprite->texture = texture;

    return sprite;
}

void destroy_quee_sprite(quee_sprite **sprite) {
    free(*sprite);
    sprite = NULL;
}
