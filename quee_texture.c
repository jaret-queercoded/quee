#include "quee_texture.h"
#include "quee_renderer.h"

#include <stdlib.h>
#include <string.h>

#include <SDL_render.h>
#include <SDL_image.h>

extern SDL_Renderer *g_renderer;

quee_texture* create_quee_texture_from_image(const char *file) {
    quee_texture* texture = malloc(sizeof(quee_texture));

    // Get the texture from the file by putting it in a surface
    // and then creating the texture from the surface
    SDL_Texture *sdl_texture = NULL;
    SDL_Surface *surface = check_sdl_ptr(IMG_Load(file)); 
    sdl_texture = check_sdl_ptr(SDL_CreateTextureFromSurface(g_renderer, surface));

    // Free the sprite after we are done with it
    SDL_FreeSurface(surface);

    texture->texture = sdl_texture;
    strcpy(texture->name, file);

    return texture;
}

void destroy_quee_texture(quee_texture **texture) {
    SDL_DestroyTexture((*texture)->texture);
    free(*texture);
    *texture = NULL;
}


quee_texture_manager* create_quee_texture_manager(uint64_t capacity) {
    quee_texture_manager *manager = malloc(sizeof(quee_texture_manager));
    manager->capacity = capacity;
    manager->nodes = malloc(sizeof(quee_texture_node *) * manager->capacity);
    for(int i = 0; i < manager->capacity; i++) {
        manager->nodes[i] = NULL;
    }
    return manager;
}

void destroy_quee_texture_manager(quee_texture_manager **manager) {
    for(int i = 0; i < (*manager)->capacity; i++) {
        if((*manager)->nodes[i] != NULL) {
            destroy_quee_texture(&(*manager)->nodes[i]->texture);
            free((*manager)->nodes[i]);
        }
    }
    free((*manager)->nodes);
    free(*manager);
    *manager = NULL;
}

quee_texture_node *create_quee_texture_node(const char *file_path, quee_texture_node *next) {
    quee_texture_node *node = malloc(sizeof(quee_texture_node));
    node->texture = create_quee_texture_from_image(file_path);
    node->next = next;
    return node;
}

quee_texture* get_quee_texture_from_texture_manager(quee_texture_manager *manager, const char *file_path) {
    int index = hash((unsigned char*)file_path) % manager->capacity;
    quee_texture *texture = NULL;
    quee_texture_node *node = NULL;
    // Todo implement external chaining
    if(manager->nodes[index] == NULL) {
        node = create_quee_texture_node(file_path, NULL);
        manager->nodes[index] = node;
        texture = node->texture;
    }
    else {
        quee_texture_node *node = manager->nodes[index]; 
        while(node) {
            if(strcmp(node->texture->name, file_path) == 0) {
                texture = node->texture;
                break;
            }
            node = node->next;
        }
        // If we make it here the texture doesn't exist and we need to add it
        node = create_quee_texture_node(file_path, manager->nodes[index]);
        manager->nodes[index] = node;
        texture = node->texture;
    }
    return texture;
}

int remove_quee_texture_from_texture_manager(quee_texture_manager *manager, const char *file_path) {
    int index = hash((unsigned char*)file_path) % manager->capacity;
    quee_texture_node *prev, *curr;
    curr = manager->nodes[index];
    prev = NULL;
    while(curr) {
        if(strcmp(curr->texture->name, file_path) == 0) {
            if(prev) {
                prev->next = curr->next;
            }
            else {
                manager->nodes[index] = curr->next;
            }
            destroy_quee_texture(&curr->texture);
            free(curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    // If we made it this far the texture doesn't exist
    quee_set_error("Texture does not exist in texture manager");
    return -1;
}
