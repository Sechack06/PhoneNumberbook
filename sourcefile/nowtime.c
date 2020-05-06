#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "node.h"
#include "file.h"
#include "nowtime.h"

char* timeretn() 
{
    struct tm* t;
    time_t timer;

    timer = time(NULL);
    t = localtime(&timer);

    char s[20];

    sprintf(s, "%04d-%02d-%02d-%02d:%02d:%02d",
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec
    );

    return s;
}