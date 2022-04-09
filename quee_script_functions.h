#ifndef QUEE_SCRIPT_FUNCTIONS_H_
#define QUEE_SCRIPT_FUNCTIONS_H_

typedef struct lua_State lua_State;
int quee_script_get_pos(lua_State *L); 
int quee_script_set_pos(lua_State *L);
int quee_script_get_delta_time(lua_State *L);
int quee_script_is_key_pressed(lua_State *L);
int quee_script_is_key_held(lua_State *L);
int quee_script_was_key_released(lua_State *L);
int quee_script_get_name(lua_State *L);
int quee_script_play_sound(lua_State *L);
#endif

