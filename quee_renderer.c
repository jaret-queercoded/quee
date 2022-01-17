#include "quee_renderer.h"

#include <SDL_render.h>

#include "quee_scene.h"
#include "quee_sprite.h"
#include "quee_helpers.h"

int quee_render_scene(SDL_Renderer* renderer, quee_scene *scene) {
    if(scene == NULL) {
        quee_set_error("Tried to render a null scene!");
        return -1;
    }
    if(!scene->render) return 0;
    for(int i = 0; i < scene->n_sprites; i++) {
        SDL_RenderCopy(renderer, scene->sprites[i]->texture, NULL, NULL);
    }
    return 0;
}
