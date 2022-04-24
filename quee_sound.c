#include "quee_sound.h"
#include "SDL_mixer.h"
#include "quee_helpers.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

quee_sound_manager* create_quee_sound_manager(uint32_t capacity) {
    quee_sound_manager *manager = malloc(sizeof(quee_sound_manager));
    manager->nodes = malloc(sizeof(quee_sound_node *) * capacity);
    for (uint32_t i = 0; i < capacity; i++) {
        manager->nodes[i] = NULL;
    }
    manager->capacity = capacity;
    return manager;
}

int quee_load_sound(quee_sound_manager* manager, const char *path) {
    int index = hash((unsigned char *)path) % manager->capacity;
    //check to see if we already have loaded said sound
    if (manager->nodes[index] != NULL && strcmp(manager->nodes[index]->sound->name, path) == 0)
        return 0;
    //no collision
    quee_sound_node *node;
    if (manager->nodes[index] == NULL) {
        manager->nodes[index] = malloc(sizeof(quee_sound_node));
        node = manager->nodes[index];
        
    }
    //we have a chain started already
    else {
        node = manager->nodes[index];
        //get to the end of the chain
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = malloc(sizeof(quee_sound_node));
        node = node->next;
    }
    node->sound = malloc(sizeof(quee_sound));
    strcpy(node->sound->name, path);
    node->next = NULL;
    node->sound->chunk = Mix_LoadWAV(path);
    if(node->sound->chunk == NULL) {
        quee_set_error("Couldn't load sound from path: %s", path);
        return -1;
    }
    return 0;
}

int quee_play_sound(quee_sound_manager* manager, const char* sound_name) {
    int index = hash((unsigned char *)sound_name) % manager->capacity;
    quee_sound_node *node = manager->nodes[index];
    while (strcmp(node->sound->name, sound_name) != 0) {
        if (node->next == NULL) {
            quee_set_error("Couldn't play sound with name: %s", sound_name);
            return -1;
        }
        node = node->next;
    }
    Mix_Chunk *chunk = node->sound->chunk; 
    Mix_PlayChannel(-1, chunk, 0);
    return 0;
}
    
void destroy_quee_sound_manager(quee_sound_manager **manager) {
    for (uint32_t i = 0; i < (*manager)->capacity; i++) {
        quee_sound_node *itr = (*manager)->nodes[i];
        while (itr) {
            quee_sound_node *next = itr->next;
            Mix_FreeChunk(itr->sound->chunk);
            free(itr->sound);
            free(itr);
            itr = next;
        }
    }
    free((*manager)->nodes);
    free(*manager);
    *manager = NULL;
}
