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
    manager->lua_state = luaL_newstate();
    luaL_openlibs(manager->lua_state);
    lua_pushcfunction(manager->lua_state, quee_script_get_pos);
    lua_setglobal(manager->lua_state, "quee_script_get_pos");
    lua_pushcfunction(manager->lua_state, quee_script_set_pos);
    lua_setglobal(manager->lua_state, "quee_script_set_pos");
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

quee_script * create_quee_script(quee_script_manager *manager, const char *path, quee_entity *entity) {
    if(path == NULL) {
        quee_set_error("Attempted to load a script with a null path");
        return NULL;
    }
    if(luaL_dofile(manager->lua_state, path)) {
        quee_set_error("Couldn't load lua script %s: %s", path, lua_tostring(manager->lua_state, -1));
        return NULL;
    }
    lua_setglobal(manager->lua_state, entity->name);
    lua_settop(manager->lua_state, 0);

    quee_script *script = malloc(sizeof(quee_script));
    script->lua_state = manager->lua_state;
    script->entity = entity;
    script->type = 0;
    //Check the script too see if it has any expected functions for later use
    if(check_script_for_function(path, "onCreate(entity)")) {
        printf("Setting on create bit\n");
        script->type |= QUEE_ON_CREATE_BIT; 
    }
    if(check_script_for_function(path, "onUpdate(entity)")) {
        script->type |= QUEE_ON_UDPATE_BIT; 
    }
    return script;
}

int run_quee_script_function(quee_script *script, const char *function) {
    //Retrieve the tabel containing the functions of the chunk
    lua_getglobal(script->lua_state, script->entity->name);
    //Get the function we want to call
    lua_getfield(script->lua_state, -1, function);
    lua_pushlightuserdata(script->lua_state, script->entity);
    if(lua_pcall(script->lua_state, 1, 0, 0) != LUA_OK) {
        quee_set_error("Couldn't run lua function %s:%s\nError: %s\n", script->entity->name, function, lua_tostring(script->lua_state, -1));
        return -1;
    }
    return 0;
}


void destroy_quee_script_manager(quee_script_manager **manager) {
    lua_close((*manager)->lua_state);
    free(*manager);
    *manager = NULL;
}

void destroy_quee_script(quee_script **script) {
    free(*script);
    *script = NULL;
}
