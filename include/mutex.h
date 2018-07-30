#ifndef _INC_MUTEX_H
#define _INC_MUTEX_H

#include <pthread.h>
#include <stdio.h>

#define mutex_t pthread_mutex_t

#define MUTEX(name) \
    pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER

void inline mutex_init(mutex_t *pmutex)
{
    pthread_mutex_init(pmutex, NULL);
}

void inline mutex_lock(mutex_t *pmutex)
{
    pthread_mutex_lock(pmutex);
}

void inline mutex_trylock(mutex_t *pmutex)
{
    pthread_mutex_trylock(pmutex);
}


void inline mutex_unlock(mutex_t *pmutex)
{
    pthread_mutex_unlock(pmutex);
}


void inline mutex_destroy(mutex_t *pmutex)
{
    pthread_mutex_destroy(pmutex);
}
#endif /* _INC_MUTEXT_H */