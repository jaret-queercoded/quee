#include "quee_script_functions.h"
#include "lua.h"

#include <stdio.h>


int quee_script_get_pos(lua_State *L) {
    const char *test = lua_tostring(L, 1);
    printf("%s\n", test);
    return 0;
}
