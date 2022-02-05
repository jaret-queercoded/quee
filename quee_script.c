#include "quee_script.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "quee_helpers.h"

#include <stdlib.h>
#include <string.h>

quee_script_manager * create_quee_script_manager(int max_scripts) {
    quee_script_manager *manager = malloc(sizeof(quee_script_manager));
    manager->lua_state = luaL_newstate();
    luaL_openlibs(manager->lua_state);
    return manager;
}

quee_script * create_quee_script(quee_script_manager *manager, const char *path) {
    printf("loading %s\n", path);
    if(path == NULL) {
        quee_set_error("Attempted to load a script with a null path");
        return NULL;
    }
    if(luaL_loadfile(manager->lua_state, path)) {
        quee_set_error("Couldn't load lua script %s", path);
        return NULL;
    }
    //Create _ENV tables
    lua_newtable(manager->lua_state);
    //Create metatable
    lua_newtable(manager->lua_state);
    //Get the global table
    lua_getglobal(manager->lua_state, "_G");
    lua_setfield(manager->lua_state, -2, "__index");
    //Set global as metatable
    lua_setmetatable(manager->lua_state, -2);
    //Push to registery with a unique name
    lua_setfield(manager->lua_state, LUA_REGISTRYINDEX, path);
    //Retrieve it
    lua_getfield(manager->lua_state, LUA_REGISTRYINDEX, path);
    //Set the upvalue (_ENV)
    lua_setupvalue(manager->lua_state, 1, 1);
    //Run chunks
    lua_pcall(manager->lua_state, 0, LUA_MULTRET, 0);

    quee_script *script = malloc(sizeof(quee_script));
    script->path = malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(script->path, path);
    return script;
}

int run_quee_script_function(quee_script_manager *manager, quee_script *script, const char *function) {
    //Retrieve the tabel containing the functions of the chunk
    lua_getfield(manager->lua_state, LUA_REGISTRYINDEX, script->path);
    //Get the function we want to call
    lua_getfield(manager->lua_state, -1, function);
    if(lua_pcall(manager->lua_state, 0, 0, 0)) {
        quee_set_error("Couldn't run lua function %s", function);
        return -1;
    }
    return 0;
}

void destroy_quee_script_manager(quee_script_manager **manager) {
    lua_close((*manager)->lua_state);
    free(*manager);
    manager = NULL;
}

void destroy_quee_script(quee_script **script) {
    free((*script)->path);
    script = NULL;
}
