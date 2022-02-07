#include "quee_script_functions.h"
#include "lua.h"
#include "quee_entity.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


inline void * check_lua_ptr_func(void *ptr, char *func)
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
    quee_entity *test = check_lua_ptr(lua_touserdata(L, 1));
    printf("%p\n", test);
    printf("%s\n", test->name);
    return 0;
}