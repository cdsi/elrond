#include <stdarg.h>
#include <stdio.h>

int
printf(const char *fmt, ...)
{
        va_list argp;
        va_start(argp, fmt);
        int rc = vprintf(fmt, argp);
        va_end(argp);
        fflush(stdout);
        return rc;
}

int
fprintf(FILE * stream, const char *fmt, ...)
{
        va_list argp;
        va_start(argp, fmt);
        int rc = vfprintf(stream, fmt, argp);
        va_end(argp);
        fflush(stream);
        return rc;
}

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
