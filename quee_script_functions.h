#ifndef QUEE_SCRIPT_FUNCTIONS_H_
#define QUEE_SCRIPT_FUNCTIONS_H_

typedef struct lua_State lua_State;
int quee_script_get_pos(lua_State *L); 
int quee_script_set_pos(lua_State *L);
#endif
