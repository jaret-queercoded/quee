#include "quee_script_functions.h"
#include "lua.h"
#include "quee_entity.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void * check_lua_ptr_func(void *ptr, const char *func)
{
    if(ptr == NULL) {
        fprintf(stderr, "quee got a null ptr from lua in %s\nPress Enter to continue...\n", func);
        getchar();
        exit(EXIT_FAILURE);
    }
    return ptr;
}

#define check_lua_ptr(ptr) check_lua_ptr_func(ptr, __func__);

int quee_script_get_pos(lua_State *L) {
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    lua_pushnumber(L, entity->pos.x);
    lua_pushnumber(L, entity->pos.y);
    return 2;
}

int quee_script_set_pos(lua_State *L) {
    //We don't have the right number of args
    if (lua_gettop(L) != 3) {
        //TODO error handling
        exit(EXIT_FAILURE);
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    double x, y;
    if(!lua_isnumber(L, 2) || !lua_isnumber(L, 3))
    {
        //TODO error handling
        exit(EXIT_FAILURE);
    }
    x = lua_tonumber(L, 2);
    y = lua_tonumber(L, 3);
    entity->pos.x = x;
    entity->pos.y = y;
    return 0;
}

int quee_script_get_delta_time(lua_State *L) {
    //We don't have the right number of args
    if (lua_gettop(L) != 1) {
        exit(EXIT_FAILURE);
    }
    quee_entity *entity = check_lua_ptr(lua_touserdata(L, 1));
    lua_pushnumber(L, entity->scene->delta_time);
    return 1;
}