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

int add_quee_script(quee_script_manager *manager, char *path) {
    if(luaL_loadfile(manager->lua_state, path)) {
        quee_set_error("Couldn't load lua script %s", path);
        return -1;
    }
    lua_pcall(manager->lua_state, 0, 0, 0);
    return 0;
}

int run_quee_script_function(quee_script_manager *manager, char *function) {
    lua_getglobal(manager->lua_state, function);
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
