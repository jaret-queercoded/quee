#pragma once

#include <stdio.h>

#define TOP_OF_TEST printf("%s\n", __func__); fflush(stdout);
#define BOTTOM_OF_TEST printf("%s: PASSED!\n", __func__); fflush(stdout);
