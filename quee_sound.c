#include "quee_sound.h"
#include "SDL_mixer.h"
#include "quee_helpers.h"
#include <stdlib.h>

quee_sound_manager* create_quee_sound_manager() {
    quee_sound_manager *manager = malloc(sizeof(quee_sound_manager));
    return manager;
}

int quee_load_sound(quee_sound_manager* manager, const char *path) {
    int index = hash((unsigned char *)path);
    manager->sound = Mix_LoadWAV(path);
    if(manager->sound == NULL) {
        quee_set_error("Couldn't load sound from path: %s", path);
        return -1;
    }
    return 0;
}

void quee_play_sound(quee_sound_manager* manager, const char* sound_name) {
    int index = hash((unsigned char *)sound_name);
    //TODO handle external chaining
    Mix_Chunk *sound = manager->nodes[index]->sound->sound; 
    Mix_PlayChannel(-1, sound, 0);
}
    
void destroy_quee_sound_manager(quee_sound_manager **manager) {
    Mix_FreeChunk((*manager)->sound);
    free(*manager);
    *manager = NULL;
}
