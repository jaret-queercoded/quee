#ifndef QUEE_SCRIPT_TEST_H_
#define QUEE_SCRIPT_TEST_H_

#include "quee_test_helper.h"

#define QUEE_SCRIPT_SUITE "quee_script"
#define QUEE_SCRIPT_MANAGER_SUITE "quee_script_manager"

quee_test_result test_quee_script_creation();
quee_test_result test_quee_script_function_type();
quee_test_result test_quee_script_run_function();

#endif
