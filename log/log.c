#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>

#include "log.h"

char *get_date(char *date)
{
    time_t timer=time(NULL);
    strftime(date, 11, "%Y-%m-%d", localtime(&timer));
    return date;
}



int logger(int log_level, char *format,...)
{
    int ret;
    va_list args;

    do {
        va_start(args, format);
        //PrintfLog(format, args);
        va_end(args);

    } while(0);
}