#include "quee_sprite.h"
#include "SDL_render.h"
#include "quee_helpers.h"

#include <SDL_render.h>
#include <SDL_image.h>


quee_sprite *create_quee_sprite_from_image_path(SDL_Renderer *renderer, const char *file) {

    // Get the texture from the file by putting it in a surface
    // and then creating the texture from the surface
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = check_sdl_ptr(IMG_Load(file)); 
    texture = check_sdl_ptr(SDL_CreateTextureFromSurface(renderer, surface));

    // Free the sprite after we are done with it
    SDL_FreeSurface(surface);
    
    // Allocate memory for the sprite
    quee_sprite *sprite = malloc(sizeof(quee_sprite));

    // Assign texture for the sprite
    sprite->texture = texture;

    return sprite;
}

void destroy_quee_sprite(quee_sprite *sprite) {
    SDL_DestroyTexture(sprite->texture);

    free(sprite);
    sprite = NULL;
}
