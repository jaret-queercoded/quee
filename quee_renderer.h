#ifndef QUEE_RENDERER_H_
#define QUEE_RENDERER_H_

typedef struct quee_scene quee_scene;
typedef struct SDL_Renderer SDL_Renderer;

int quee_render_scene(SDL_Renderer* renderer, quee_scene* scene);
void quee_toggle_debug_render();

#endif
