/*
    error.c --
    Error logging
*/

#include "osd.h"

void error_init(void)
{
}

void error_shutdown(void)
{
}

void error(char *format, ...)
{
    (void) format;
    printf("ERROR");
    // va_list ap;
    // va_start(ap, format);
    // printf(format, ap);
    // va_end(ap);
}
