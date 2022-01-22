#include "quee_test_helper.h"

quee_test_result create_quee_test_result(bool result, const char *name) {
    quee_test_result test_result;
    test_result.result = result;
    strcpy(test_result.name, name);
    return test_result;
}
