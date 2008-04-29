#include "common.h"

#include <glib.h>

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT gdouble
xul_xtime(xul_t * xul, gdouble offset)
{
        g_assert(XUL_IS_VALID(xul));

        GTimeVal tv;

        g_get_current_time(&tv);

        if (offset < 0) {
                xul->time->tv.tv_sec = tv.tv_sec;
                xul->time->tv.tv_usec = tv.tv_usec;
                return (gdouble) 0;
        }

        /* return current time in seconds minus an offset as a gdouble */
        return (gdouble) (tv.tv_sec - xul->time->tv.tv_sec) +
          ((gdouble) (tv.tv_usec - xul->time->tv.tv_usec) / 1.e6) - offset;
}

XUL_APIEXPORT gdouble
xul_xtime_overhead(xul_t * xul)
{
        gdouble t0 = xul_xtime(xul, 0);
        gdouble t1 = t0 + .2;

        gint32 i = 0;

        while (xul_xtime(xul, 0) < t1)
                i++;

        return t1 = .2 / (gdouble) i;
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
