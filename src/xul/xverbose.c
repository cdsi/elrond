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

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif                          /* HAVE_ERRNO_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT xul_verbose_level_e
xul_verbose_level_conv(xul_t * xul, gint verbose)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_level_e level = XUL_VERBOSE_LEVEL_0;

        switch (verbose) {
        case 0:
                level = XUL_VERBOSE_LEVEL_0;
                break;
        case 1:
                level = XUL_VERBOSE_LEVEL_1;
                break;
        case 2:
                level = XUL_VERBOSE_LEVEL_2;
                break;
        case 3:
                level = XUL_VERBOSE_LEVEL_3;
                break;
        case 4:
                level = XUL_VERBOSE_LEVEL_4;
                break;
        case 5:
                level = XUL_VERBOSE_LEVEL_5;
                break;
        case 6:
                level = XUL_VERBOSE_LEVEL_6;
                break;
        case 7:
                level = XUL_VERBOSE_LEVEL_7;
                break;
        case 8:
                level = XUL_VERBOSE_LEVEL_8;
                break;
        case 9:
                level = XUL_VERBOSE_LEVEL_9;
                break;
        default:
                level = XUL_VERBOSE_LEVEL_0;
                break;
        }

        return level;
}

XUL_APIEXPORT xul_verbose_level_e
xul_verbose_level_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->verbose->level;
}

XUL_APIEXPORT void
xul_verbose_level_set(xul_t * xul, xul_verbose_level_e level)
{
        g_assert(XUL_IS_VALID(xul));

        xul->verbose->level = level;
}

XUL_APIEXPORT void
xul_verbose_output_close(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        if (!xul->verbose->fp) {
                return;
        }

        fclose(xul->verbose->fp);
}

XUL_APIEXPORT xul_rc_t
xul_verbose_output_open(xul_t * xul, const gchar * output)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_output_close(xul);

        xul->verbose->fp = g_fopen(output, "a+");

        if (xul->verbose->fp) {
                return XUL_SUCCESS;
        }

        xul_error_add(xul, XUL_ERROR, XUL_ERROR_FILEIO, "Unable to open %s: %s", output, g_strerror(errno));

        return XUL_FAILURE;
}

XUL_APIEXPORT void
xul_verbose_handler_default(const gchar * domain, GLogLevelFlags level, const gchar * message, gpointer __xul)
{
        xul_t *xul = (xul_t *) __xul;

        g_assert(XUL_IS_VALID(xul));

        if (xul_verbose_level_get(xul) < level) {
                return;
        }

        if (!xul->verbose->fp) {
                return;
        }

        fprintf(xul->verbose->fp, "%s\n", message);
        fflush(xul->verbose->fp);
}

XUL_APIEXPORT xul_verbose_handler_f
xul_verbose_handler_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->verbose->handler;
}

XUL_APIEXPORT void
xul_verbose_handler_set(xul_t * xul, xul_verbose_handler_f handler)
{
        g_assert(XUL_IS_VALID(xul));

        g_log_set_handler(XUL_VERBOSE_DOMAIN, G_LOG_LEVEL_MASK, handler, xul);
}

void
xul_verbose_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        free(verbose);
}

xul_verbose_t *
xul_verbose_alloc()
{
        xul_verbose_t *verbose = (xul_verbose_t *) malloc(sizeof(xul_verbose_t));

        memset(verbose, 0, sizeof(xul_verbose_t));
        verbose->magic = XUL_VERBOSE_MAGIC;

        return verbose;
}

void
xul_verbose_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        xul_verbose_output_close(xul);

        xul_verbose_free(xul);
}

xul_verbose_t *
xul_verbose_new()
{
        xul_verbose_t *verbose = xul_verbose_alloc();

        return verbose;
}

void
xul_verbose_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        xul_verbose_handler_set(xul, xul_verbose_handler_default);
        xul_verbose_level_set(xul, XUL_VERBOSE_LEVEL_0);
        xul_verbose_output_open(xul, "/dev/stdout");
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
