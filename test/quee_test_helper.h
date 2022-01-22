#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct quee_test_result quee_test_result;

struct quee_test_result {
    bool result;
    char name[256];
    char msg[256];
    char file[256];
    int line;
};

#define QUEE_ASSERT(test, msg) if(!(test)) return create_quee_test_result(false, __func__, msg, __FILE__, __LINE__) 

#define QUEE_PASSED create_quee_test_result(true, __func__, "", "", 0)

quee_test_result create_quee_test_result(bool result, const char *name, const char *msg, const char *file, int line);
