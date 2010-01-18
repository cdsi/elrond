#include "elrond_common.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif                          /* HAVE_STDLIB_H */

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif                          /* HAVE_STDIO_H */

#ifdef HAVE_STRING_H
#include <string.h>
#endif                          /* HAVE_STRING_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT gdouble
xul_time(xul_t * xul, gdouble offset)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        GTimeVal tv;

        g_get_current_time(&tv);

        /* return current time in seconds minus an offset as a gdouble */
        return (gdouble) (tv.tv_sec - xul->time->tv.tv_sec) +
          ((gdouble) (tv.tv_usec - xul->time->tv.tv_usec) / 1.e6) - offset;
}

XUL_APIEXPORT gdouble
xul_time0(xul_t * xul)
{
        return xul_time(xul, 0);
}

XUL_APIEXPORT gdouble
xul_time_overhead(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        gdouble t0 = xul_time(xul, 0);
        gdouble t1 = t0 + .2;

        gint32 i = 0;

        while (xul_time0(xul) < t1) {
                i++;
        }

        return t1 = .2 / (gdouble) i;
}

XUL_APIEXPORT const gchar *
xul_time_iso8601_r(xul_t *xul, gchar *buffer, gsize bufferlen)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        GTimeVal tv;

        g_get_current_time(&tv);

        const gchar *message = g_time_val_to_iso8601(&tv);
        g_snprintf(buffer, bufferlen, "%s", message);
        g_free((gpointer)message);

        return buffer;
}

XUL_APIEXPORT const gchar *
xul_time_iso8601(xul_t *xul)
{
        static gchar buffer[256];

        return xul_time_iso8601_r(xul, &buffer[0], sizeof(buffer));
}

void
xul_time_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        free(xtime);
}

xul_time_t *
xul_time_alloc()
{
        xul_time_t *xtime = (xul_time_t *) malloc(sizeof(xul_time_t));

        memset(xtime, 0, sizeof(xul_time_t));
        xtime->magic = XUL_TIME_MAGIC;

        return xtime;
}

void
xul_time_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        xul_time_free(xul);
}

xul_time_t *
xul_time_new()
{
        xul_time_t *xtime = xul_time_alloc();

        return xtime;
}

void
xul_time_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_time_t *xtime = xul->time;
        g_assert(XUL_TIME_IS_VALID(xtime));

        /* NOOP */
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
