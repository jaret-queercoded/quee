#include "quee_scene_test.h"

#include "../quee_scene.h"
#include "../quee_texture.h"
#include "../quee_script.h"
#include "quee_test_helper.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

quee_test_result test_quee_scene_manager_creation() {
    const int max_cap = 1;
    // Create a scene and check to make sure the values are what they should be
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    QUEE_ASSERT(manager->current_capacity == 0, "Capcity wasn't zero");
    QUEE_ASSERT(manager->max_capacity == max_cap, "Max cap wasn't right");
    // Destroy the manager because we are done with it
    destroy_quee_scene_manager(&manager);
    // Make sure the pointer is NULL so that we don't have a dangling pointer
    QUEE_ASSERT(manager == NULL, "Scene Manager left a dangling pointer");
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
        QUEE_ASSERT(quee_scene_manager_insert(manager, scene) == 0, "Scene insertion failed");
    }

    QUEE_ASSERT(manager->max_capacity == 10, "Didn't exapnd size correctly");
    QUEE_ASSERT(manager->current_capacity == 10, "Not the expected number of items");
    QUEE_ASSERT(strcmp(manager->scenes[0]->name, "0") == 0, "First scene wasn't right");
    QUEE_ASSERT(strcmp(manager->scenes[9]->name, "9") == 0, "Last scene wasn't right");

    // Attempt to add a scene that already has this name
    // It should fail
    quee_scene* scene = create_quee_scene();
    strcpy(scene->name , "0");
    QUEE_ASSERT(quee_scene_manager_insert(manager, scene) == -1, "Scene insertion should of failed");
    destroy_quee_scene_manager(&manager);
    QUEE_ASSERT(manager == NULL, "Scene Manager left a dangling pointer");
    return QUEE_PASSED;
}

quee_test_result test_quee_scene_manager_remove_scene() {
    const int max_cap = 2;
    quee_scene_manager* manager = create_quee_scene_manager(max_cap);
    quee_scene *s1 = create_quee_scene();
    quee_scene *s2 = create_quee_scene();
    strcpy(s1->name, "s1");
    strcpy(s2->name, "s2");
    QUEE_ASSERT(quee_scene_manager_insert(manager, s1) == 0, "First scene insertion failed");
    QUEE_ASSERT(quee_scene_manager_insert(manager, s2) == 0, "Second scene insertion failed");
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s3") == -1, "Removal should have failed");
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s1") == 0, "s1 wasn't removed");
    QUEE_ASSERT(manager->current_capacity == 1, "Capcity wasn't correct after deletion");
    QUEE_ASSERT(strcmp(manager->scenes[0]->name, "s2") == 0, "s2 wasn't the first scene");
    QUEE_ASSERT(quee_scene_manager_remove(manager, "s2") == 0, "s2 wasn't removed");
    QUEE_ASSERT(manager->current_capacity == 0, "More than one scene left");
    destroy_quee_scene_manager(&manager);
    QUEE_ASSERT(manager == NULL, "Scene manager left a dangling pointer");
    return QUEE_PASSED;
}

quee_test_result test_quee_scene_creation() {
    quee_scene *scene = create_quee_scene();
    QUEE_ASSERT(scene != NULL, "Didn't get a scene");
    QUEE_ASSERT(strcmp(scene->name, "") == 0, "Name should have been empty");
    QUEE_ASSERT(scene->entities == NULL, "There should be no entities");
    QUEE_ASSERT(scene->max_entities == 0, "The max entities should be zero");
    QUEE_ASSERT(scene->current_entities == 0, "Current entities should be zero");
    destroy_quee_scene(&scene);
    QUEE_ASSERT(scene == NULL, "Scene was left dangling");
    return QUEE_PASSED;
}

quee_test_result test_quee_load_scene() {
    quee_texture_manager *texture_manager = create_quee_texture_manager(10);
    quee_script_manager *script_manager = create_quee_script_manager(10);
    quee_scene *scene = load_quee_scene("assets/test/testscene.json", NULL, texture_manager, script_manager);
    QUEE_ASSERT(scene != NULL, "Couldn't get a scene");
    QUEE_ASSERT(strcmp(scene->name, "test_scene1") == 0, "Name wasn't what was expected");
    QUEE_ASSERT(scene->render, "We should want to render this scene");
    QUEE_ASSERT(scene->current_entities == 1, "We should have 1 sprite in this scene");
    QUEE_ASSERT(scene->max_entities == 1, "We should have a max of 1 sprite in this scene");
    QUEE_ASSERT(scene->entities[0], "We should have a sprite");
    destroy_quee_scene(&scene);
    QUEE_ASSERT(scene == NULL, "Scene was left dangling");
    return QUEE_PASSED;
}
