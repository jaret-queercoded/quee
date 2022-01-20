#include "quee_texture.h"
#include "quee_renderer.h"

#include <stdlib.h>
#include <string.h>

#include <SDL_render.h>
#include <SDL_image.h>

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
    texture = NULL;
}


quee_texture_manager* create_quee_texture_manager(uint64_t capacity) {
    quee_texture_manager *manager = malloc(sizeof(quee_texture_manager));
    manager->capacity = capacity;
    manager->textures = malloc(sizeof(quee_texture *) * manager->capacity);
    for(int i = 0; i < manager->capacity; i++) {
        manager->textures[i] = NULL;
    }
    return manager;
}

void destroy_quee_texture_manager(quee_texture_manager **manager) {
    for(int i = 0; i < (*manager)->capacity; i++) {
        if((*manager)->textures[i] != NULL)
            destroy_quee_texture(&(*manager)->textures[i]);
    }
    free((*manager)->textures);
    free(*manager);
    manager = NULL;
}

quee_texture* get_quee_texture_from_texture_manager(quee_texture_manager *manager, const char *file_path) {
    int index = hash((unsigned char*)file_path) % manager->capacity;
    // Todo implement external chaining
    if(manager->textures[index] == NULL) {
        manager->textures[index] = create_quee_texture_from_image(file_path);
    }
    return manager->textures[index];
}
