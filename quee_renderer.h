#pragma once

typedef struct quee_scene quee_scene;
typedef struct SDL_Renderer SDL_Renderer;

int quee_render_scene(SDL_Renderer* renderer, quee_scene* scene);
