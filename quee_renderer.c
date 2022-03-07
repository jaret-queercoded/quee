#include "quee_renderer.h"

#include <SDL_render.h>

#include "quee_scene.h"
#include "quee_sprite.h"
#include "quee_helpers.h"
#include "quee_entity.h"

static bool g_render_debug_info = false;

void render_entity(quee_entity *entity, SDL_Renderer *renderer) {
    if(entity->type & QUEE_SPRITE_BIT){
        quee_sprite *sprite = entity->sprite; 
        SDL_Rect src_rect = {.x = sprite->curr_frame->pos.x,
                             .y = sprite->curr_frame->pos.y,
                             .w = sprite->curr_frame->size.x,
                             .h = sprite->curr_frame->size.y};
        SDL_Rect dst_rect = {.x = entity->pos.x,
                             .y = entity->pos.y,
                             .w = sprite->curr_frame->size.x,
                             .h = sprite->curr_frame->size.y};
        SDL_Texture *texture = entity->sprite->texture->texture;
        SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
    }
}

void render_debug(quee_entity *entity, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    if(entity->type & QUEE_BOX_COLLIDER_BIT){
        SDL_Rect debug_box;
        debug_box.x = entity->pos.x;
        debug_box.y = entity->pos.y;
        debug_box.w = entity->box_collider->size.x;
        debug_box.h = entity->box_collider->size.y;
        SDL_RenderDrawRect(renderer, &debug_box);
    }
}

void quee_toggle_debug_render() {
    g_render_debug_info = !g_render_debug_info;
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
    if(g_render_debug_info) {
        for(int i = 0; i < scene->current_entities; i++) {
            render_debug(scene->entities[i], renderer);
        }
    }
    return 0;
}
