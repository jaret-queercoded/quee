#ifndef QUEE_HELPERS_H_
#define QUEE_HELPERS_H_

#include <stdint.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define TARGET_FPS 120
#define TICKS_PER_FRAME (1000.0f / TARGET_FPS)

#define MAX_STR_LEN 256

typedef struct Pixel Pixel;

struct Pixel {
    uint8_t B;
    uint8_t G;
    uint8_t R;
    uint8_t A;
};

void check_sdl_code(int code);
void* check_sdl_ptr(void *ptr);

void check_quee_code(int code);
void* check_quee_ptr(void *ptr);
void quee_set_error(char* format, ...);
char* quee_get_error();

unsigned long hash(unsigned char *str);

#endif
