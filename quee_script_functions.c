#include "quee_script_functions.h"
#include "lua.h"
#include "quee_entity.h"
#include "quee_global_manager.h"
#include "quee_helpers.h"
#include "quee_sound.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern quee_global_manager *g_quee_manager;

void quee_lua_failure_func(const char *func, const char *error) {
    fprintf(stderr, "quee encountered an error in: %s: %s\n", func, error);
    exit(EXIT_FAILURE);
}

#define quee_lua_failure(error) quee_lua_failure_func(__func__, error); 

void * check_lua_ptr_func(void *ptr, const char *func)
{
    if(ptr == NULL) {
        fprintf(stderr, "quee got a null ptr from lua in %s\nPress Enter to continue...\n", func);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

#define check_lua_ptr(ptr) check_lua_ptr_func(ptr, __func__);

int quee_script_get_pos(lua_State *L) {
    if (lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isuserdata(L, 1)) {
        quee_lua_failure("Expected a pointer to the entity!");
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    lua_pushnumber(L, entity->pos.x);
    lua_pushnumber(L, entity->pos.y);
    return 2;
}

int quee_script_set_pos(lua_State *L) {
    if (lua_gettop(L) != 3) {
        quee_lua_failure("Expected 3 arguments!");
    }
    if(!lua_isuserdata(L, 1)) {
        quee_lua_failure("Expected entity ptr as first argument!");
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    double x, y;
    if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3))
    {
        quee_lua_failure("Expected x and y position!");
    }
    x = lua_tonumber(L, 2);
    y = lua_tonumber(L, 3);
    entity->pos.x = x;
    entity->pos.y = y;
    return 0;
}

int quee_script_get_delta_time(lua_State *L) {
    if (lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isuserdata(L, 1)) {
        quee_lua_failure("Expected entity ptr as first argument to get delta time!");
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    lua_pushnumber(L, entity->scene->delta_time);
    return 1;
}

int quee_script_is_key_held(lua_State *L) {
    if(lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isstring(L, 1)) {
        quee_lua_failure("Expected a string of a key to look for");
    }
    const char* key = lua_tostring(L, 1);
    bool pressed = quee_input_is_held(g_quee_manager->input_manager, key);
    lua_pushboolean(L, pressed);
    return 1;
}

int quee_script_is_key_pressed(lua_State *L) {
    if(lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isstring(L, 1)) {
        quee_lua_failure("Expected a string of a key to look for");
    }
    const char* key = lua_tostring(L, 1);
    bool pressed = quee_input_is_pressed(g_quee_manager->input_manager, key);
    lua_pushboolean(L, pressed);
    return 1;
}

int quee_script_was_key_released(lua_State *L) {
    if(lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isstring(L, 1)) {
        quee_lua_failure("Expected a string of a key to look for");
    }
    const char* key = lua_tostring(L, 1);
    bool released = quee_input_was_released(g_quee_manager->input_manager, key);
    lua_pushboolean(L, released);
    return 1;
}

int quee_script_get_name(lua_State *L) {
    if(lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isuserdata(L, 1)) {
        quee_lua_failure("Expected entity ptr as first argument!");
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    lua_pushstring(L, entity->name);
    return 1;
}
int quee_script_play_sound(lua_State *L) {
    if(lua_gettop(L) != 1) {
        quee_lua_failure("Expected a single argument!");
    }
    if(!lua_isstring(L, 1)) {
        quee_lua_failure("Expected a path to a sound!");
    }
    const char* sound_name = lua_tostring(L, 1);
    check_quee_code(quee_play_sound(g_quee_manager->sound_manager, sound_name));
    return 0;
}
