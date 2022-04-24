#ifndef QUEE_THREAD_H_
#define QUEE_THREAD_H_

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#include <stdint.h>

typedef struct quee_thread_work quee_thread_work;
typedef struct quee_thread_pool quee_thread_pool;

typedef void (*quee_thread_func)(void *arg);

struct quee_thread_work {
    quee_thread_func func;
    void *arg;
    quee_thread_work *next;
};

struct quee_thread_pool {
    quee_thread_work *work_first;
    quee_thread_work *work_last;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cond;
    pthread_cond_t working_cond;
    size_t working_count;
    size_t thread_count;
    bool stop;
};

quee_thread_pool * create_quee_thread_pool(uint32_t size);
void destroy_quee_thread_pool(quee_thread_pool **pool);

bool quee_thread_pool_add_work(quee_thread_pool *pool, quee_thread_func func, void *arg);
void quee_thread_pool_wait(quee_thread_pool *pool);

#endif
