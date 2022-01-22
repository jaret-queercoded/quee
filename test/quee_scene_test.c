#include "quee_scene_test.h"

#include "../quee_scene.h"
#include "../quee_texture.h"
#include "quee_test_helper.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

quee_test_result test_quee_scene_manager_creation() {
    const int max_cap = 1;
    // Create a scene and check to make sure the values are what they should be
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    QUEE_ASSERT(manager->current_capacity == 0);
    QUEE_ASSERT(manager->max_capacity == max_cap);
    // Destroy the manager because we are done with it
    destroy_quee_scene_manager(&manager);
    // Make sure the pointer is NULL so that we don't have a dangling pointer
    QUEE_ASSERT(manager == NULL);
    return QUEE_PASSED;
}

quee_test_result test_quee_scene_manager_add_scene() {
    const int max_cap = 5;
    
    // Add 4 scenes 1 below cap
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    for(int i = 0; i < max_cap * 2; i++) {
        quee_scene* scene = create_quee_scene();
        int len = snprintf(NULL, 0, "%d", i);
        char *name = malloc(len + 1);
        snprintf(name, len + 1, "%d", i);
        strcpy(scene->name, name);
        QUEE_ASSERT(quee_scene_manager_insert(manager, scene) == 0);
    }

    QUEE_ASSERT(manager->max_capacity == 10);
    QUEE_ASSERT(manager->current_capacity == 10);
    QUEE_ASSERT(strcmp(manager->scenes[0]->name, "0") == 0);
    QUEE_ASSERT(strcmp(manager->scenes[9]->name, "9") == 0);

    // Attempt to add a scene that already has this name
    // It should fail
    quee_scene* scene = create_quee_scene();
    strcpy(scene->name , "0");
    QUEE_ASSERT(quee_scene_manager_insert(manager, scene) == -1);
    destroy_quee_scene_manager(&manager);
    QUEE_ASSERT(manager == NULL);
    return QUEE_PASSED;
}

quee_test_result test_quee_scene_manager_remove_scene() {
    const int max_cap = 2;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    quee_scene *s1 = create_quee_scene();
    quee_scene *s2 = create_quee_scene();
    strcpy(s1->name, "s1");
    strcpy(s2->name, "s2");
    QUEE_ASSERT(quee_scene_manager_insert(manager, s1) == 0);
    QUEE_ASSERT(quee_scene_manager_insert(manager, s2) == 0);
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s3") == -1);
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s1") == 0);
    QUEE_ASSERT(manager->current_capacity == 1);
    QUEE_ASSERT(strcmp(manager->scenes[0]->name, "s2") == 0);
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s2") == 0);
    QUEE_ASSERT(manager->current_capacity == 0);
    destroy_quee_scene_manager(&manager);
    QUEE_ASSERT(manager == NULL);
    return QUEE_PASSED;
}

quee_test_result test_quee_scene_creation() {
    quee_scene *scene = create_quee_scene();
    QUEE_ASSERT(scene != NULL);
    QUEE_ASSERT(strcmp(scene->name, "") == 0);
    QUEE_ASSERT(scene->sprites == NULL);
    QUEE_ASSERT(scene->max_sprites == 0);
    QUEE_ASSERT(scene->current_sprites == 0);
    destroy_quee_scene(&scene);
    QUEE_ASSERT(scene == NULL);
    return QUEE_PASSED;
}

quee_test_result test_quee_load_scene() {
    quee_texture_manager *texture_manager = create_quee_texture_manager(10);
    quee_scene *scene = load_quee_scene("test/testscene.json", NULL, texture_manager);
    QUEE_ASSERT(scene != NULL);
    QUEE_ASSERT(strcmp(scene->name, "test_scene1") == 0);
    QUEE_ASSERT(scene->render);
    destroy_quee_scene(&scene);
    QUEE_ASSERT(scene == NULL);
    return QUEE_PASSED;
}
