#include "quee_script_test.h"
#include "../quee_script.h"
#include "../quee_entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_SCRIPT_PATH "assets/test/scripts/test.lua"

quee_test_result test_quee_script_creation() {
    quee_script_manager *manager = create_quee_script_manager();
    QUEE_ASSERT(manager, "We should have a manager after creation");
    QUEE_ASSERT(manager->L, "We should have a lua state after creation");
    quee_scene *scene = create_quee_scene();
    quee_entity *entity = create_quee_entity(scene);
    entity->name = malloc(sizeof(char) * 5);
    strcpy(entity->name, "test");
    quee_script *script = create_quee_script(manager, TEST_SCRIPT_PATH, entity);
    QUEE_ASSERT(script, "We should have a script now");
    QUEE_ASSERT(script->L == manager->L, "Script and manager should have the same lua state");
    QUEE_ASSERT(script->entity == entity, "Script and entity should match");
    destroy_quee_script(&script);
    QUEE_ASSERT(script == NULL, "Dangling script ptr!");
    destroy_quee_script_manager(&manager);
    QUEE_ASSERT(manager == NULL, "Dangling manager ptr!");
    destroy_quee_scene(&scene);
    destroy_quee_entity(&entity);
    return QUEE_PASSED;
}

quee_test_result test_quee_script_function_type() {
    quee_script_manager *manager = create_quee_script_manager();
    quee_scene *scene = create_quee_scene();
    quee_entity *entity = create_quee_entity(scene);
    entity->name = malloc(sizeof(char) * 5);
    strcpy(entity->name, "test");
    quee_script *script = create_quee_script(manager, TEST_SCRIPT_PATH, entity);
    QUEE_ASSERT(script->type == 2, "We should have a type mask of 2 for onUpdate!");
    destroy_quee_script(&script);
    destroy_quee_script_manager(&manager);
    destroy_quee_scene(&scene);
    destroy_quee_entity(&entity);
    return QUEE_PASSED;
}

quee_test_result test_quee_script_run_function() {
    quee_script_manager *manager = create_quee_script_manager();
    quee_scene *scene = create_quee_scene();
    quee_entity *entity = create_quee_entity(scene);
    entity->name = malloc(sizeof(char) * 5);
    strcpy(entity->name, "test");
    quee_script *script = create_quee_script(manager, TEST_SCRIPT_PATH, entity);
    int result = run_quee_script_function(script, "onUpdate");
    QUEE_ASSERT(result == 0, "We didn't run the script correctly!");
    destroy_quee_script(&script);
    destroy_quee_script_manager(&manager);
    destroy_quee_scene(&scene);
    destroy_quee_entity(&entity);
    return QUEE_PASSED;
}
