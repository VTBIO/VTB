#ifndef _INC_MUTEX_H
#define _INC_MUTEX_H

#include <pthread.h>
#include <stdio.h>

#define MUTEX(name) \
    pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER

#define mutex_init(name) \
    pthread_mutex_init(&name, NULL);

#define mutex_lock(name) \
    pthread_mutex_lock(&name);

#define mutex_trylock(name) \
    pthread_mutex_trylock(&name);

#define mutex_unlock(name) \
    pthread_mutex_unlock(&name);

#define mutex_destroy(name)
    pthread_mutex_destroy(&name);

#endif /* _INC_MUTEXT_H */