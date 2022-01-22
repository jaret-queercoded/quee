#include "quee_sprite_test.h"

#include "../quee_sprite.h"
#include "../quee_texture.h"
#include "quee_test_helper.h"

quee_test_result test_quee_sprite_creation() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_sprite *sprite = create_quee_sprite(get_quee_texture_from_texture_manager(manager, "assets/test/test.png"), (vec2i){0,0}, (vec2i){0,0});
    QUEE_ASSERT(sprite, "We didn't get a sprite back");
    destroy_quee_sprite(&sprite);
    QUEE_ASSERT(sprite == NULL, "Sprite destroy left a dangling pointer");
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}
