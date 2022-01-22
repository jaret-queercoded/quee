#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct quee_test_result quee_test_result;

struct quee_test_result {
    bool result;
    char name[256];
};

#define QUEE_ASSERT(test) if(!(test)) return create_quee_test_result(false, __func__) 

#define QUEE_PASSED create_quee_test_result(true, __func__)

quee_test_result create_quee_test_result(bool result, const char *name);
