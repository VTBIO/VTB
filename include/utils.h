#ifndef _LIB_UTILS_H
#define _LIB_UTILS_H

/**
 *  sizeof an array
 */
#define ARRAY_SIZE(array) \
    (sizeof(array) /sizeof((array)[0]))

#define swap(x, y) \
    do { typeof(a) _tmp = (a); (a) = (b); (b) = _tmp; } while(0)

#define offsetof(type, member) (size_t)&(((type*)0)->member)

#define container_of(ptr, type, member) ({ \
    void *__mptr = (void *)(ptr); \
    ((type *)(__mptr - offsetof(type, member))); })

#endif /* _LIB_UTILS_H */