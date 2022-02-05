#ifndef QUEE_SCRIPT_H_
#define QUEE_SCRIPT_H_

#include <stdint.h>

typedef struct lua_State lua_State;

typedef struct quee_script_manager quee_script_manager;
typedef struct quee_script quee_script;

struct quee_script_manager {
    lua_State *lua_state;
};

struct quee_script {
    char *path;
};

quee_script_manager * create_quee_script_manager(int max_scripts);
quee_script * create_quee_script(quee_script_manager *manager, const char *path);
int run_quee_script_function(quee_script_manager *manager, quee_script *script, const char *function);
void destroy_quee_script_manager(quee_script_manager **manager);
void destroy_quee_script(quee_script **script);

#endif

