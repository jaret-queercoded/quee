#include "quee_scene.h"
#include "quee_sprite.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <json_object.h>
#include <json_tokener.h>


quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer* renderer) {
    FILE *fp;
    char buffer[1024];
    json_object *parsed_json;
    json_object *sprites;
    json_object *sprite_path;
    quee_scene* scene = malloc(sizeof(quee_scene));
    fp = fopen(scene_path, "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "sprites", &sprites);
    scene->n_sprites = json_object_array_length(sprites); 
    scene->sprites = malloc(scene->n_sprites * sizeof(quee_sprite));
    for(size_t i = 0; i < scene->n_sprites; i++) {
        sprite_path = json_object_array_get_idx(sprites, i);
        scene->sprites[i] = create_quee_sprite_from_image_path(renderer, json_object_get_string(sprite_path)); 
    }
    return scene;
}

void destroy_quee_scene(quee_scene *scene) {
    for(int i = 0; i < scene->n_sprites; i++) {
        destroy_quee_sprite(scene->sprites[i]);
    }

    free(scene);
}
