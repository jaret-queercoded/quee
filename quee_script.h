#ifndef QUEE_SCRIPT_H_
#define QUEE_SCRIPT_H_

#include <stdint.h>

typedef struct lua_State lua_State;
typedef struct quee_entity quee_entity;

typedef struct quee_script_manager quee_script_manager;
typedef struct quee_script quee_script;

struct quee_script_manager {
    lua_State *L;
};

#define QUEE_ON_CREATE_BIT 0x01
#define QUEE_ON_UDPATE_BIT 0x02
#define QUEE_ON_COLLIDE_BIT 0x04
struct quee_script {
    lua_State *L;
    quee_entity *entity;
    uint32_t type:3;
};

quee_script_manager * create_quee_script_manager();
quee_script * create_quee_script(quee_script_manager *manager, const char *path, quee_entity *entity);
int run_quee_script_function(quee_script *script, const char *function, void *arg);
void destroy_quee_script_manager(quee_script_manager **manager);
void destroy_quee_script(quee_script **script);

#endif

