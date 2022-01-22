#include "quee_renderer.h"

#include <SDL_render.h>

#include "quee_scene.h"
#include "quee_sprite.h"
#include "quee_helpers.h"
#include "quee_entity.h"

void render_entity(quee_entity *entity, SDL_Renderer *renderer) {
    if(entity->type & QUEE_SPRITE_BIT){
        quee_sprite *sprite = entity->sprite; 
        SDL_Rect src_rect = {.x = sprite->curr_frame * sprite->frame_size.x,
                             .y = 0,
                             .w = sprite->frame_size.x,
                             .h = sprite->frame_size.y};
        SDL_Rect dst_rect = {.x = sprite->pos.x,
                             .y = sprite->pos.y,
                             .w = sprite->frame_size.x,
                             .h = sprite->frame_size.y};
        SDL_Texture *texture = entity->sprite->texture->texture;
        SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
    }
}

int quee_render_scene(SDL_Renderer* renderer, quee_scene *scene) {
    if(scene == NULL) {
        quee_set_error("Tried to render a null scene!");
        return -1;
    }
    if(!scene->render) return 0;
    for(int i = 0; i < scene->current_entities; i++) {
        render_entity(scene->entities[i], renderer);
    }
    return 0;
}
