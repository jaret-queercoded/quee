#include "quee_script_functions.h"
#include "lua.h"
#include "quee_entity.h"

#include <stdio.h>


int quee_script_get_pos(lua_State *L) {
    quee_entity *test = (quee_entity *)lua_touserdata(L, 1);
    printf("%s\n", test->name);
    return 0;
}