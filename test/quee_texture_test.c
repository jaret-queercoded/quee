#include "quee_texture_test.h"
#include "../quee_texture.h"

#include "quee_test_helper.h"

#include <assert.h>
#include <string.h>

void test_quee_texture_creation_and_deletion() {
    TOP_OF_TEST
    const char *fp = "assets/test.png";
    quee_texture *texture = create_quee_texture_from_image(fp);
    assert(texture);
    assert(strcmp(texture->name, fp) == 0);
    assert(texture->texture);
    BOTTOM_OF_TEST
}
