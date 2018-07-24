#ifndef _INC_THREAD_H
#define _INC_THREAD_H

#include <pthread.h>

struct thread_context {
    void *arg;
    int (*entry)(void *arg);

    pthread_t tid;
};


int create_thread(struct thread_context *context);

#endif /* _INC_THREAD_H */