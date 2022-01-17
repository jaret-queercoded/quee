#include "quee_scene_test.h"
#include "quee_test_helper.h"

#include "../quee_scene.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_quee_scene_manager_creation() {
    TOP_OF_TEST
    const int max_cap = 1;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    assert(manager->current_capacity == 0);
    assert(manager->max_capacity == max_cap);
    destroy_quee_scene_manager(&manager);
    assert(manager == NULL);
    BOTTOM_OF_TEST
}

void test_quee_scene_manager_add_scene() {
    TOP_OF_TEST
    const int max_cap = 5;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    for(int i = 0; i < max_cap-1; i++) {
        quee_scene* scene = load_quee_scene("testscene.json", NULL);
        int len = snprintf(NULL, 0, "%d", i);
        char *name = malloc(len + 1);
        snprintf(name, len + 1, "%d", i);
        scene->name = name;
        assert(quee_scene_manager_insert(manager, scene) == 0);
    }
    quee_scene* scene = load_quee_scene("testscene.json", NULL);
    scene->name = "1";
    assert(quee_scene_manager_insert(manager, scene) == -1);
    assert(manager->current_capacity == 4);
    scene->name = "5";
    assert(quee_scene_manager_insert(manager, scene) == 0);
    assert(quee_scene_manager_insert(manager, scene) == -1);
    destroy_quee_scene_manager(&manager);
    BOTTOM_OF_TEST
}

void test_quee_scene_manager_remove_scene() {
    TOP_OF_TEST
    
    BOTTOM_OF_TEST
}
