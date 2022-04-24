#include "quee_thread.h"
#include "quee_helpers.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>



static quee_thread_work * quee_thread_pool_create_work(quee_thread_func func, void *arg) {
    quee_thread_work *work;
    if(func == NULL)
        return NULL;
    work = malloc(sizeof(quee_thread_work));
    work->func = func;
    work->arg = arg;
    work->next = NULL;
    return work;
}

static void quee_thread_pool_destroy_work(quee_thread_work *work) {
    if(work == NULL)
        return;
    free(work);
}

static quee_thread_work * quee_thread_pool_get_work(quee_thread_pool *pool) {
    quee_thread_work *work;
    if(pool == NULL) return NULL;
    work = pool->work_first;
    //No work to do
    if(work == NULL) return NULL;

    //Got the last job
    if(work->next == NULL) {
        pool->work_first = NULL;
        pool->work_last = NULL;
    }
    else {
        pool->work_first = work->next;
    }
    return work;
}

static void * quee_thread_worker(void *arg) {
    quee_thread_pool *pool = arg;
    quee_thread_work *work;
    //Keep the thread running so that we can reuse it
    while (1) {
        //Lock the pool so nothing else can mess with it
        pthread_mutex_lock(&(pool->work_mutex));
        //check for work and if there is none wait for work
        //this will automatically unlock the mutex for others to use
        while (pool->work_first == NULL && !pool->stop) {
            pthread_cond_wait(&(pool->work_cond), &(pool->work_mutex));
        }
        //If we want to stop break out so that we can stop using the thread
        if(pool->stop) {
            break;
        }

        //get work to do and increate working count also unlock mutex so others can get work
        work = quee_thread_pool_get_work(pool);
        pool->working_count++;
        pthread_mutex_unlock(&(pool->work_mutex));

        //if we got back work do the work and then clean up the work
        if(work != NULL) {
            work->func(work->arg);
            quee_thread_pool_destroy_work(work);
        }

        //lock the pool so that we can reduce the number of workers since we are done
        pthread_mutex_lock(&(pool->work_mutex));
        pool->working_count--;
        //let others know that we are done and that they can get work if they are waiting for us
        if(!pool->stop && pool->working_count == 0 && pool->work_first == NULL) {
            pthread_cond_signal(&(pool->working_cond));
        }
        //unlock because we have finished
        pthread_mutex_unlock(&(pool->work_mutex));
    }
    pool->thread_count--;
    pthread_cond_signal(&(pool->working_cond));
    pthread_mutex_unlock(&(pool->work_mutex));

    return NULL;
}

quee_thread_pool * create_quee_thread_pool(uint32_t size) 
{
    quee_thread_pool *pool;
    pthread_t thread;

    if (size <= 0) {
        quee_set_error("Cannot create a thread pool with zero threads!");
        return NULL;
    }

    pool = malloc(sizeof(quee_thread_pool));
    pool->thread_count = size;
    pthread_mutex_init(&(pool->work_mutex), NULL);
    pthread_cond_init(&(pool->work_cond), NULL);
    pthread_cond_init(&(pool->working_cond), NULL);
    pool->work_first = NULL;
    pool->work_last = NULL;

    for(uint32_t i = 0; i < size; i++) {
        pthread_create(&thread, NULL, quee_thread_worker, pool);
        pthread_detach(thread);
    }
    return pool;
}

void destroy_quee_thread_pool(quee_thread_pool **pool_ptr_ptr) {
    quee_thread_pool *pool = *pool_ptr_ptr;
    quee_thread_work *work;
    quee_thread_work *work_next;

    
    //If threre is no pool nothing to clean up
    if(pool == NULL) {
        return;
    }

    //Lock so no more work comes in while we are trying to clean up
    pthread_mutex_lock(&(pool->work_mutex));

    //clean up all of our to be done work
    work = pool->work_first;
    while (work != NULL) {
        work_next = work->next;
        quee_thread_pool_destroy_work(work);
        work = work_next;
    }
    
    //Let everyone remaining know to stop
    pool->stop = true;
    pthread_cond_broadcast(&(pool->work_cond));
    pthread_mutex_unlock(&(pool->work_mutex));

    //Wait for everyone to finish up
    quee_thread_pool_wait(pool);

    //Destroy our mutex and conditions
    pthread_mutex_destroy(&(pool->work_mutex));
    pthread_cond_destroy(&(pool->work_cond));
    pthread_cond_destroy(&(pool->working_cond));

    free(pool);
    pool_ptr_ptr = NULL;
}

bool quee_thread_pool_add_work(quee_thread_pool *pool, quee_thread_func func, void *arg) {
    quee_thread_work *work;
    //No pool no work
    if(pool == NULL) {
        return false;
    }
    //Try and create work
    work = quee_thread_pool_create_work(func, arg);
    //Coulnd't create work
    if(work == NULL) {
        return false;
    }
    //Lock pool so we can add in the work
    pthread_mutex_lock(&(pool->work_mutex));
    //No work currently
    if(pool->work_first == NULL) {
        pool->work_first = work;
        pool->work_last = pool->work_first;
    }
    else {
        pool->work_last->next = work;
        pool->work_last = work;
    }

    //let everyone know there is work
    pthread_cond_broadcast(&(pool->work_cond));
    pthread_mutex_unlock(&(pool->work_mutex));

    return true;
}

void quee_thread_pool_wait(quee_thread_pool *pool) {
    if(pool == NULL) {
        return;
    }

    //Lock the mutex so there nothing else can come in
    pthread_mutex_lock(&(pool->work_mutex));

    //Wait for stuff to finish up
    while(1) {
        if((!pool->stop && pool->working_count != 0) || (pool->stop && pool->thread_count != 0)) {
            pthread_cond_wait(&(pool->working_cond), &(pool->work_mutex));
        } else {
            break;
        }
    }

    //Everything is done so  we can unlock;
    pthread_mutex_unlock(&(pool->work_mutex));
}
