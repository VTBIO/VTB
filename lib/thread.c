#include <pthread.h>

#include "thread.h"

static void func_entry(void *arg)
{
    struct thread_context *context = arg;
    if (context->entry != NULL) {
        context->entry(context->arg);
    }
}

int create_thread(struct thread_context *context)
{
    int ret;

    ret = pthread_create(&context->tid, NULL, func_entry, (void *)context);
    if (ret != 0) {
        return ret;
    }

    return 0;
}