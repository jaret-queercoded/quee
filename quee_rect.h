#ifndef QUEE_RECT_H_
#define QUEE_RECT_H_

#include <stdint.h>

typedef struct quee_rect quee_rect;

struct quee_rect {
    uint32_t x, y, w, h;
};

#endif

