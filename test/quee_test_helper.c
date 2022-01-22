#include "quee_test_helper.h"

quee_test_result create_quee_test_result(bool result, const char *name, const char* msg, const char* file, int line) {
    quee_test_result test_result;
    test_result.result = result;
    strcpy(test_result.name, name);
    strcpy(test_result.msg, msg);
    strcpy(test_result.file, file);
    test_result.line = line;
    return test_result;
}
