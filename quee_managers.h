#ifndef QUEE_MANAGERS_H_
#define QUEE_MANAGERS_H_

#define BASE_CAPACITY 10

typedef struct quee_managers quee_managers;
typedef struct quee_texture_manager quee_texture_manager;
typedef struct quee_scene_manager quee_scene_manager;

struct quee_managers {
    quee_texture_manager* texture_manager;
    quee_scene_manager* scene_manager;
};

quee_managers* create_quee_managers();
void destroy_quee_managers(quee_managers **managers);

#endif

