#include "quee_scene_test.h"

#include "../quee_scene.h"

#include <assert.h>

void test_scene_manager_creation() {
    const int max_cap = 1;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    assert(manager->current_capacity == 0);
    assert(manager->max_capacity == max_cap);
}

void failure() {
    assert(false);
}
