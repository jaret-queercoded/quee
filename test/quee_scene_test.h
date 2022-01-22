#ifndef QUEE_SCENE_TEST_H_
#define QUEE_SCENE_TEST_H_

#include "quee_test_helper.h"

#define QUEE_SCENE_SUITE "quee_scene"
#define QUEE_SCENE_MANAGER_SUITE "quee_scene_manager"

quee_test_result test_quee_scene_manager_creation();
quee_test_result test_quee_scene_manager_add_scene();
quee_test_result test_quee_scene_manager_remove_scene();

quee_test_result test_quee_scene_creation();
quee_test_result test_quee_load_scene();

#endif
