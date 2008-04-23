#include "common.h"

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

/*
 * XUL Verbose API
 */

xul_verbose_t *
verbose_alloc()
{
        xul_verbose_t *verbose = (xul_verbose_t *) malloc(sizeof(xul_verbose_t));

        memset(verbose, 0, sizeof(xul_verbose_t));

        return verbose;
}

void
verbose_free(xul_verbose_t * verbose)
{
        free(verbose);
}

XUL_APIEXPORT int32_t
xul_verbose_level_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->verbose->level;
}

XUL_APIEXPORT void
xul_verbose_level_set(xul_t * xul, int32_t level)
{
        g_assert(XUL_IS_VALID(xul));

        xul->verbose->level = level;
}

XUL_APIEXPORT void
xul_verbose_output_open(xul_t * xul, const char *filename)
{
        g_assert(XUL_IS_VALID(xul));

        xul->verbose->fp = fopen(filename, "a+");

        if (!xul->verbose->fp) {
                xul->rc = XUL_EFOPEN;
                return;
        }

        xul->rc = XUL_SUCCESS;
}

XUL_APIEXPORT void
xul_verbose_output_close(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        fclose(xul->verbose->fp);

        xul->rc = XUL_SUCCESS;
}

void
verbose_handler(const gchar * domain, GLogLevelFlags level, const gchar * message, gpointer data)
{
        xul_t *xul = (xul_t *) data;

        g_assert(XUL_IS_VALID(xul));

        if (xul->verbose->level < level) {
                return;
        }

        fprintf(xul->verbose->fp, "[%s] %s\n", domain, message);
        fflush(xul->verbose->fp);
}

void
verbose_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul->verbose->fp = stdout;
        g_log_set_handler("XUL", G_LOG_LEVEL_MASK, verbose_handler, xul);
}

void
verbose_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        fclose(xul->verbose->fp);
}

/*
 * XUL API
 */

xul_t *
xul_alloc()
{
        xul_t *xul = (xul_t *) malloc(sizeof(xul_t));

        memset(xul, 0, sizeof(xul_t));
        xul->magic = XUL_MAGIC;
        xul->verbose = verbose_alloc();

        return xul;
}

void
xul_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        verbose_free(xul->verbose);
        free(xul);
}

XUL_APIEXPORT xul_t *
xul_init()
{
        xul_t *xul = xul_alloc();

        verbose_init(xul);

        return xul;
}

XUL_APIEXPORT void
xul_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        verbose_delete(xul);
        xul_free(xul);
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
