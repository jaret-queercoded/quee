#ifndef QUEE_SOUND_H_
#define QUEE_SOUND_H_

#include "quee_helpers.h"
#include <SDL_mixer.h>
#include <stdint.h>

typedef struct quee_sound quee_sound;
typedef struct quee_sound_node quee_sound_node;
typedef struct quee_sound_manager quee_sound_manager;
struct quee_sound {
    char name[MAX_STR_LEN];
    Mix_Chunk *sound;
};

struct quee_sound_node {
    quee_sound *sound;
    quee_sound_node *next;
};

struct quee_sound_manager {
    quee_sound_node **nodes;
    uint64_t capacity;
};

quee_sound_manager* create_quee_sound_manager();
int quee_load_sound(quee_sound_manager *manager, const char *path);
void quee_play_sound(quee_sound_manager *manager, const char *sound_name);
void destroy_quee_sound_manager(quee_sound_manager **manager);

#endif
