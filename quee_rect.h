#ifndef quee_vec2f_H_
#define quee_vec2f_H_

#include <stdint.h>

typedef struct quee_vec2f quee_vec2f;
typedef struct quee_vec2i quee_vec2i;

struct quee_vec2f {
    double x, y;
};
struct quee_vec2i {
    int64_t x, y;
};
#endif

