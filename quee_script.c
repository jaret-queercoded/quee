#include "quee_script.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "quee_helpers.h"
#include "quee_script_functions.h"
#include "quee_entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


quee_script_manager * create_quee_script_manager() {
    quee_script_manager *manager = malloc(sizeof(quee_script_manager));
    manager->L = luaL_newstate();
    luaL_openlibs(manager->L);

    //TODO figure out a way to register all of my functions a more generic way
    lua_pushcfunction(manager->L, quee_script_get_pos);
    lua_setglobal(manager->L, "quee_script_get_pos");
    lua_pushcfunction(manager->L, quee_script_set_pos);
    lua_setglobal(manager->L, "quee_script_set_pos");
    lua_pushcfunction(manager->L, quee_script_get_delta_time);
    lua_setglobal(manager->L, "quee_script_get_delta_time");
    lua_pushcfunction(manager->L, quee_script_is_key_held);
    lua_setglobal(manager->L, "quee_script_is_key_held");
    lua_pushcfunction(manager->L, quee_script_is_key_pressed);
    lua_setglobal(manager->L, "quee_script_is_key_pressed");
    lua_pushcfunction(manager->L, quee_script_was_key_released);
    lua_setglobal(manager->L, "quee_script_was_key_released");
    lua_pushcfunction(manager->L, quee_script_get_name);
    lua_setglobal(manager->L, "quee_script_get_name");
    return manager;
}

// TODO there has to be a better way to do this because it is very error prone
// and likely to flag a file that actually doesn't contain the function that 
// we are looking for
bool check_script_for_function(const char *path, const char *function) {
    FILE *fp = fopen(path, "r");
    char string[50];
    while(fscanf(fp,"%s",string) == 1) {
        if(strstr(string, function) != 0) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

//TODO need to make sure that all entities have a unique name or maybe should use their id instead of their name
//not entirely sure
quee_script * create_quee_script(quee_script_manager *manager, const char *path, quee_entity *entity) {
    if(path == NULL) {
        quee_set_error("Attempted to load a script with a null path");
        return NULL;
    }
    //Load the information from the script
    if(luaL_dofile(manager->L, path)) {
        quee_set_error("Couldn't load lua script %s: %s", path, lua_tostring(manager->L, -1));
        return NULL;
    }
    //Create a table to store the infomation that we loaded
    //We use the entity name as the name so that we can have multiple entities using the same script
    //If we just use the path like I initially tried we will overwrite the functions and all entities
    //That use the same script will use the same local variables
    lua_setglobal(manager->L, entity->name);
    lua_settop(manager->L, 0);

    //Create the script that we are going to return
    quee_script *script = malloc(sizeof(quee_script));
    script->L = manager->L;
    script->entity = entity;
    script->type = 0;
    //Check the script too see if it has any expected functions for later use
    if(check_script_for_function(path, "onCreate(entity)")) {
        script->type |= QUEE_ON_CREATE_BIT; 
    }
    if(check_script_for_function(path, "onUpdate(entity)")) {
        script->type |= QUEE_ON_UDPATE_BIT; 
    }
    if(check_script_for_function(path, "onCollision(entity")) {
        script->type |= QUEE_ON_COLLIDE_BIT; 
    }
    return script;
}

int run_quee_script_function(quee_script *script, const char *function, void *arg) {
    int args = arg ? 2 : 1;
    //Retrieve the tabel containing the script for the entity
    lua_getglobal(script->L, script->entity->name);
    //Get the function we want to call
    lua_getfield(script->L, -1, function);
    //All of quees defined functions require at least the entity so we push that here
    lua_pushlightuserdata(script->L, script->entity);
    //Sometimes we need to pass in an extra pointer like when we collide
    if(arg != NULL) {
        lua_pushlightuserdata(script->L, arg);
    }
    if(lua_pcall(script->L, args, 0, 0) != LUA_OK) {
        quee_set_error("Couldn't run lua function %s:%s\nError: %s\n", script->entity->name, function, lua_tostring(script->L, -1));
        return -1;
    }
    return 0;
}


void destroy_quee_script_manager(quee_script_manager **manager) {
    lua_close((*manager)->L);
    free(*manager);
    *manager = NULL;
}

void destroy_quee_script(quee_script **script) {
    free(*script);
    *script = NULL;
}
