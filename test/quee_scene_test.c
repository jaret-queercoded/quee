#include "quee_scene_test.h"
#include "quee_test_helper.h"

#include "../quee_scene.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_quee_scene_manager_creation() {
    TOP_OF_TEST
    const int max_cap = 1;
    // Create a scene and check to make sure the values are what they should be
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    assert(manager->current_capacity == 0);
    assert(manager->max_capacity == max_cap);
    // Destroy the manager because we are done with it
    destroy_quee_scene_manager(&manager);
    // Make sure the pointer is NULL so that we don't have a dangling pointer
    assert(manager == NULL);
    BOTTOM_OF_TEST
}

void test_quee_scene_manager_add_scene() {
    TOP_OF_TEST
    const int max_cap = 5;
    
    // Add 4 scenes 1 below cap
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    for(int i = 0; i < max_cap * 2; i++) {
        quee_scene* scene = create_quee_scene();
        int len = snprintf(NULL, 0, "%d", i);
        char *name = malloc(len + 1);
        snprintf(name, len + 1, "%d", i);
        scene->name = name;
        assert(quee_scene_manager_insert(manager, scene) == 0);
    }

    assert(manager->max_capacity == 10);
    assert(manager->current_capacity == 10);
    assert(strcmp(manager->scenes[0]->name, "0") == 0);
    assert(strcmp(manager->scenes[9]->name, "9") == 0);

    // Attempt to add a scene that already has this name
    // It should fail
    quee_scene* scene = create_quee_scene();
    scene->name = "0";
    assert(quee_scene_manager_insert(manager, scene) == -1);
    destroy_quee_scene_manager(&manager);
    assert(manager == NULL);
    BOTTOM_OF_TEST
}

void test_quee_scene_manager_remove_scene() {
    TOP_OF_TEST
    const int max_cap = 2;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    quee_scene *s1 = create_quee_scene();
    quee_scene *s2 = create_quee_scene();
    s1->name = "s1";
    s2->name = "s2";
    assert(quee_scene_manager_insert(manager, s1) == 0);
    assert(quee_scene_manager_insert(manager, s2) == 0);
    assert(quee_scene_manager_remove(manager, "s3") == -1);
    assert(quee_scene_manager_remove(manager, "s1") == 0);
    assert(manager->current_capacity == 1);
    assert(strcmp(manager->scenes[0]->name, "s2") == 0);
    assert(quee_scene_manager_remove(manager, "s2") == 0);
    assert(manager->current_capacity == 0);
    destroy_quee_scene_manager(&manager);
    assert(manager == NULL);
    BOTTOM_OF_TEST
}

void test_quee_scene_creation() {
    TOP_OF_TEST
    quee_scene *scene = create_quee_scene();
    assert(scene != NULL);
    assert(strcmp(scene->name, "") == 0);
    assert(scene->sprites == NULL);
    assert(scene->max_sprites == 0);
    assert(scene->current_sprites == 0);
    destroy_quee_scene(&scene);
    assert(scene == NULL);
    BOTTOM_OF_TEST
}

void test_quee_load_scene() {
    TOP_OF_TEST
    quee_scene *scene = load_quee_scene("test/testscene.json", NULL);
    assert(scene != NULL);
    assert(strcmp(scene->name, "test_scene1") == 0);
    assert(scene->render);
    destroy_quee_scene(&scene);
    assert(scene == NULL);
    BOTTOM_OF_TEST
}

