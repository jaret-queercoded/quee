#include "quee_scene.h"
#include "quee_helpers.h"
#include "quee_sprite.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <json_object.h>
#include <json_tokener.h>

quee_scene_manager* create_quee_scene_manager(uint64_t max_capacity) {
    quee_scene_manager *manager = malloc(sizeof(quee_scene_manager));
    manager->max_capacity = max_capacity;
    manager->scenes = malloc(sizeof(quee_scene *) * manager->max_capacity);
    manager->current_capacity = 0;
    return manager;
}

int quee_scene_manager_insert(quee_scene_manager *manager, quee_scene *scene) {
    if(manager->current_capacity == manager->max_capacity) {
        quee_set_error("Scene manager is already at max capcity"); 
        return -1;
    }
    if(scene == NULL) {
        quee_set_error("Scene manager was given a null scene");
        return -1;
    }
    for(int i = 0; i < manager->current_capacity; i++) {
        if(strcmp(manager->scenes[i]->name, scene->name) == 0) {
            quee_set_error("Scene already exists with that name");
            return -1;
        }
    }
    manager->scenes[manager->current_capacity++] = scene;
    return 0;
}

int quee_scene_manager_remove(quee_scene_manager *manager, char *scene_name) {
    int index = 0;
    for(; index < manager->current_capacity; index++) {
        const char *name = manager->scenes[index]->name;
        if(strcmp(scene_name, name) == 0) {
            destroy_quee_scene(&manager->scenes[index]);  
            break;
        }
    }
    if(index == manager->current_capacity) {
        quee_set_error("Couldn't find a scene by that name!");
        return -1;
    }
    for(; index < manager->current_capacity - 1; index++) {
        quee_scene *s1, *s2;
        s1 = manager->scenes[index];
        s2 = manager->scenes[index + 1];
        manager->scenes[index] = s2;
        manager->scenes[index + 1] = s1;
    }
    manager->current_capacity--;
    return 0;
}

void destroy_quee_scene_manager(quee_scene_manager **manager) {
    for(int i = 0; i < (*manager)->current_capacity; i++) {
        destroy_quee_scene(&(*manager)->scenes[i]);
    }
    free((*manager)->scenes);
    free(*manager);
    *manager = NULL;
}

quee_scene* create_quee_scene() {
    quee_scene* scene = malloc(sizeof(quee_scene));
    scene->n_sprites = 0;
    scene->name = "";
    scene->render = NULL;
    scene->sprites = NULL;
    return scene;
}

quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer* renderer) {
    FILE *fp;
    char buffer[1024];
    json_object *parsed_json;
    json_object *sprites;
    json_object *sprite_path;
    json_object *name;
    json_object *render;
    quee_scene* scene = malloc(sizeof(quee_scene));
    fp = fopen(scene_path, "r");
    if(fp == NULL) {
        quee_set_error("Coulnd't open file");
        return NULL;
    }
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "name", &name);
    scene->name = json_object_get_string(name);

    json_object_object_get_ex(parsed_json, "render", &render);
    scene->render = json_object_get_boolean(render);

    json_object_object_get_ex(parsed_json, "sprites", &sprites);
    scene->n_sprites = json_object_array_length(sprites); 
    scene->sprites = malloc(scene->n_sprites * sizeof(quee_sprite));
    for(size_t i = 0; i < scene->n_sprites; i++) {
        sprite_path = json_object_array_get_idx(sprites, i);
        scene->sprites[i] = create_quee_sprite_from_image_path(renderer, json_object_get_string(sprite_path)); 
    }
    return scene;
}

void destroy_quee_scene(quee_scene **scene) {
    for(int i = 0; i < (*scene)->n_sprites; i++) {
        destroy_quee_sprite((*scene)->sprites[i]);
    }

    free(*scene);
    *scene = NULL;
}
