#include "quee_texture_test.h"
#include "../quee_texture.h"

#include "quee_test_helper.h"

#include <assert.h>
#include <string.h>

const char *fp = "assets/test/test.png";

quee_test_result test_quee_texture_creation_and_deletion() {
    quee_texture *texture = create_quee_texture(fp);
    QUEE_ASSERT(texture, "Didn't get a quee texture back!");
    QUEE_ASSERT(strcmp(texture->name, fp) == 0, "Name was not what was expected!");
    QUEE_ASSERT(texture->texture, "Quee texture didn't have a sdl2 texture!");
    destroy_quee_texture(&texture);
    QUEE_ASSERT(texture == NULL, "Texture left a dangling pointer!");
    return QUEE_PASSED;
}

quee_test_result test_quee_texture_manager_creation_and_deletion() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    QUEE_ASSERT(manager, "We didn't create a texture manager!");
    QUEE_ASSERT(manager->capacity == 1, "Texture manager capacity should have been 1");
    destroy_quee_texture_manager(&manager);
    QUEE_ASSERT(manager == NULL, "Destroying texture manager left dangling");
    return QUEE_PASSED;
}

quee_test_result test_quee_get_texture() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_texture *texture = quee_texture_manager_get(manager, fp);
    QUEE_ASSERT(texture, "We didn't get a texture back");
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}

quee_test_result test_quee_remove_texture() {
    quee_texture_manager *manager = create_quee_texture_manager(1);
    quee_texture_manager_get(manager, fp);
    QUEE_ASSERT(quee_texture_manager_remove(manager, fp) == 0, "Couldn't remove the texture");
    QUEE_ASSERT(quee_texture_manager_remove(manager, fp) == -1, "Shouldn't have been able to remove");
    destroy_quee_texture_manager(&manager);
    return QUEE_PASSED;
}
