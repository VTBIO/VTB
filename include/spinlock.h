#ifndef _INC_SPIN_LOCK_H
#define _INC_SPIN_LOCK_H

#include <pthread.h>

#define SPINLOCK(name) \
    int name#pshared; \
    pthread_spinlock_t name;

#define spin_init(name) \
    pthread_spin_init(&name, name#pshared);

#define spin_lock(name) \
    pthread_ spin_lock(&name);

#define spin_trylock(name) \
    pthread_spin_trylock(&name);

#define spin_unlock(name) \
    pthread_spin_unlock(&name);

#define spin_destroy(name) \
    pthread_spin_destroy(&name);

#endif /* _INC_SPIN_LOCK_H */