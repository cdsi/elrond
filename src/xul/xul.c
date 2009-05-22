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

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif                          /* HAVE_UNISTD_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT gpointer *
xul_userdata_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->userdata;
}

XUL_APIEXPORT void
xul_userdata_set(xul_t * xul, gpointer * userdata)
{
        g_assert(XUL_IS_VALID(xul));

        xul->userdata = userdata;
}

void
xul_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        free(xul);
}

xul_t *
xul_alloc()
{
        xul_t *xul = (xul_t *) malloc(sizeof(xul_t));

        memset(xul, 0, sizeof(xul_t));
        xul->magic = XUL_MAGIC;

        return xul;
}

XUL_APIEXPORT void
xul_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_delete(xul);
        xul_time_delete(xul);
        xul_verbose_delete(xul);
        xul_error_delete(xul);

        xul_free(xul);
}

XUL_APIEXPORT xul_t *
xul_new()
{
        xul_t *xul = xul_alloc();

        xul->prefs = xul_prefs_new();
        xul->time = xul_time_new();
        xul->verbose = xul_verbose_new();
        xul->error = xul_error_new();

        return xul;
}

XUL_APIEXPORT void
xul_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_init(xul);
        xul_time_init(xul);
        xul_verbose_init(xul);
        xul_error_init(xul);
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
