#ifndef _LOG_LOG_H
#define _LOG_LOG_H

#include <stdio.h>

#define MAX_LOG_LEN (256)

typedef enum {
    NONE = 0,
    INFO = 1,
    DEBUG = 2,
    WARNING = 3,
    ERROR = 4,
} LOGLEVEL;

int logger(int log_level, char *format,...);


#endif /* _LOG_LOG_H */