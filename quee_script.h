#ifndef QUEE_SCRIPT_H_
#define QUEE_SCRIPT_H_

#include <stdint.h>

typedef struct lua_State lua_State;

typedef struct quee_script_manager quee_script_manager;
typedef struct quee_script quee_script;

struct quee_script_manager {
    lua_State *lua_state;
    char **scripts;
    uint64_t max_scripts;
    uint64_t curr_scripts;
};

quee_script_manager * create_quee_script_manager(int max_scripts);
int add_quee_script(quee_script_manager *manager, char *path);
int run_quee_scripts(quee_script_manager *manager, char *function);
void destroy_quee_script_manager(quee_script_manager **manager);

#endif

