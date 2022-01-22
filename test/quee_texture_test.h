#ifndef QUEE_TEXTURE_TEST_H_
#define QUEE_TEXTURE_TEST_H_

#include "quee_test_helper.h"

#define QUEE_TEXTURE_SUITE "quee_texture"
#define QUEE_TEXTURE_MANAGER_SUITE "quee_texture_manager"

quee_test_result test_quee_texture_creation_and_deletion();

quee_test_result test_quee_texture_manager_creation_and_deletion();
quee_test_result test_quee_get_texture();
quee_test_result test_quee_remove_texture();

#endif

