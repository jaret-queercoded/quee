#include "quee_texture_test.h"
#include "../quee_texture.h"

#include "quee_test_helper.h"

#include <assert.h>
#include <string.h>

quee_test_result test_quee_texture_creation_and_deletion() {
    const char *fp = "assets/test.png";
    quee_texture *texture = create_quee_texture_from_image(fp);
    QUEE_ASSERT(texture);
    QUEE_ASSERT(strcmp(texture->name, fp) == 0);
    QUEE_ASSERT(texture->texture);
    return QUEE_PASSED;
}
