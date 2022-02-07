#include "quee_scene.h"
#include "quee_helpers.h"
#include "quee_entity.h"
#include "quee_script.h"
#include "quee_texture.h"
#include "quee_sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <json_object.h>
#include <json_tokener.h>

quee_scene_manager* create_quee_scene_manager(uint64_t max_capacity) {
    quee_scene_manager *manager = malloc(sizeof(quee_scene_manager));
    manager->max_capacity = max_capacity;
    manager->scenes = malloc(sizeof(quee_scene *) * manager->max_capacity);
    for(int i = 0; i < manager->max_capacity; i++) {
        manager->scenes[i] = NULL;
    }
    manager->current_capacity = 0;
    return manager;
}

int quee_scene_manager_insert(quee_scene_manager *manager, quee_scene *scene) {
    if(scene == NULL) {
        quee_set_error("Scene manager was given a null scene");
        return -1;
    }
    // Check to make sure that there isn't a name colision
    for(int i = 0; i < manager->current_capacity; i++) {
        if(strcmp(manager->scenes[i]->name, scene->name) == 0) {
            quee_set_error("Scene already exists with that name");
            return -1;
        }
    }
    // If we are at max capcity lets resize kinda like a vector in c++
    if(manager->current_capacity == manager->max_capacity) {
        manager->max_capacity *= 2;
        quee_scene **new_scenes = malloc(sizeof(quee_scene *) * manager->max_capacity); 
        int i = 0;
        // Copy the pointers from the old
        for(; i < manager->current_capacity; i++) {
            new_scenes[i] = manager->scenes[i];
        }
        // NULL out the rest
        for(; i < manager->max_capacity; i++) {
            new_scenes[i] = NULL;
        }
        // Free the old scenes pointer so we don't leak
        free(manager->scenes);
        manager->scenes = new_scenes;
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
    scene->current_entities = 0;
    scene->max_entities = 0;
    strcpy(scene->name, "");
    scene->render = false;
    scene->entities = NULL;
    return scene;
}

quee_scene* load_quee_scene(const char *scene_path, SDL_Renderer* renderer, quee_texture_manager *texture_manager, quee_script_manager *script_manager) {
    FILE *fp;
    char buffer[1024];
    json_object *parsed_json;
    json_object *entities_json;
    json_object *entity_json;
    json_object *enetity_type_json;
    json_object *scene_name_json;
    json_object *render_json;
    quee_scene* scene = malloc(sizeof(quee_scene));
    fp = fopen(scene_path, "r");
    if(fp == NULL) {
        quee_set_error("Coulnd't open file");
        return NULL;
    }
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "name", &scene_name_json);
    strcpy(scene->name, json_object_get_string(scene_name_json));

    json_object_object_get_ex(parsed_json, "render", &render_json);
    scene->render = json_object_get_boolean(render_json);

    json_object_object_get_ex(parsed_json, "entities", &entities_json);
    scene->current_entities = json_object_array_length(entities_json);
    scene->max_entities = scene->current_entities;
    scene->entities = malloc(scene->current_entities * sizeof(quee_entity));
    for(size_t i = 0; i < scene->current_entities; i++) {
        entity_json = json_object_array_get_idx(entities_json, i);
        json_object_object_get_ex(entity_json, "type", &enetity_type_json);
        quee_entity *entity = create_quee_entity();
        //Get the entity's name
        json_object *name;
        json_object_object_get_ex(entity_json, "name", &name);
        entity->name = malloc(sizeof(char) * (strlen(json_object_get_string(name)) + 1));
        strcpy(entity->name, json_object_get_string(name));
        json_object *pos_json;
        json_object_object_get_ex(entity_json, "pos", pos_json);
        int pos_x = json_object_get_int(json_object_array_get_idx(pos_json, 0));
        int pos_y = json_object_get_int(json_object_array_get_idx(pos_json, 1));
        entity->pos.x = pos_x;
        entity->pos.y = pos_y;
        int expected_type = json_object_get_int(enetity_type_json);
        //Check the type and load each part of the type
        //Loading sprite
        if(expected_type & QUEE_SPRITE_BIT) {
            // Get the path to the texture
            json_object *sprite_path_json;
            json_object_object_get_ex(entity_json, "path", &sprite_path_json);
            quee_texture *texture = 
                check_quee_ptr(quee_texture_manager_get(texture_manager, json_object_get_string(sprite_path_json)));
            quee_sprite *sprite = create_quee_sprite(texture);
            // Load the frame information
            json_object *frame_array_json;
            json_object_object_get_ex(entity_json, "frames", &frame_array_json);
            int number_of_frames = json_object_array_length(frame_array_json);
            quee_sprite_init_frames(sprite, number_of_frames);
            json_object *frame_info_json;
            for(size_t i = 0; i < number_of_frames; i++) {
                frame_info_json = json_object_array_get_idx(frame_array_json, i);
                int x = json_object_get_int(json_object_array_get_idx(frame_info_json, 0));
                int y = json_object_get_int(json_object_array_get_idx(frame_info_json, 1));
                int w = json_object_get_int(json_object_array_get_idx(frame_info_json, 2));
                int h = json_object_get_int(json_object_array_get_idx(frame_info_json, 3));
                int ticks = json_object_get_int(json_object_array_get_idx(frame_info_json, 4));
                quee_frame frame = { .pos = { .x = x, .y = y}, .size = { .x = w, .y =h }, .ticks = ticks };
                quee_sprite_add_frame(sprite, frame);
            }
            check_quee_code(add_to_quee_entity(entity, QUEE_SPRITE_BIT, sprite));
        }
        //Loading script
        if(expected_type & QUEE_SCRIPT_BIT) {
            json_object *script_path_json;
            json_object_object_get_ex(entity_json, "script", &script_path_json);
            const char *path = json_object_get_string(script_path_json);
            quee_script *script = 
                check_quee_ptr(create_quee_script(script_manager, path));
            //Save the entity later so that I can pass the pointer to lua
            script->entity = entity;
            check_quee_code(add_to_quee_entity(entity, QUEE_SCRIPT_BIT, script));
            if(entity->script->type & QUEE_ON_CREATE_BIT) {
                printf("Trying to run on create\n");
                check_quee_code(run_quee_script_function(entity->script, "onCreate"));
            }
        }
        assert(entity->type == expected_type);
        scene->entities[i] = entity; 
    }
    return scene;
}

int quee_scene_add_entity(quee_scene *scene, quee_entity *entity) {
    if(entity == NULL) {
        quee_set_error("Tried to add a null entity!");
        return -1;
    }
    if(scene->current_entities == scene->max_entities) {
        scene->max_entities *= 2;
        quee_entity **new_entities = malloc(sizeof(quee_scene *) * scene->max_entities); 
        int i = 0;
        // Copy the pointers from the old
        for(; i < scene->current_entities; i++) {
            new_entities[i] = scene->entities[i];
        }
        // NULL out the rest
        for(; i < scene->max_entities; i++) {
            new_entities[i] = NULL;
        }
        // Free the old entities pointer so we don't leak
        free(scene->entities);
        scene->entities = new_entities;
    }
    scene->entities[scene->current_entities++] = entity;
    return 0;
}

void update_quee_scene(quee_scene *scene, unsigned int delta_ticks) {
    for(int i = 0; i < scene->current_entities; i++) {
        update_quee_entity(scene->entities[i], delta_ticks);
    }
}

void destroy_quee_scene(quee_scene **scene) {
    for(int i = 0; i < (*scene)->current_entities; i++) {
        destroy_quee_entity(&(*scene)->entities[i]);
    }
    free((*scene)->entities);
    free(*scene);
    *scene = NULL;
}
