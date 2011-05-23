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

XUL_APIEXPORT xul_verbose_mask_e
xul_verbose_mask_conv(xul_t * xul, guint32 verbose)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_mask_e mask = XUL_VERBOSE_MASK_0x0000;

        for (guint32 i = 0; i < 32; i++) {
                if (verbose & (0x0001 << i)) {
                        mask |= 1 << (G_LOG_LEVEL_USER_SHIFT + i);
                }
        }

        return mask;
}

XUL_APIEXPORT xul_verbose_mask_e
xul_verbose_mask_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->verbose->mask;
}

XUL_APIEXPORT void
xul_verbose_mask_set(xul_t * xul, xul_verbose_mask_e mask)
{
        g_assert(XUL_IS_VALID(xul));

        xul->verbose->mask = mask;
}

XUL_APIEXPORT void
xul_verbose_filter_default(const gchar * domain, xul_verbose_mask_e masks, const gchar * message,
                           gpointer __xul)
{
        xul_t *xul = (xul_t *) __xul;

        g_assert(XUL_IS_VALID(xul));

        if (masks != XUL_VERBOSE_MASK_0x0000) {
                if (!(xul_verbose_mask_get(xul) & masks)) {
                        return;
                }
        }

        if (!xul->verbose->fp) {
                return;
        }

        g_fprintf(xul->verbose->fp, "%s\n", message);
        fflush(xul->verbose->fp);
}

XUL_APIEXPORT void
xul_verbose_filter_time0(const gchar * domain, xul_verbose_mask_e masks, const gchar * message,
                         gpointer __xul)
{
        xul_t *xul = (xul_t *) __xul;

        g_assert(XUL_IS_VALID(xul));

        if (masks != XUL_VERBOSE_MASK_0x0000) {
                if (!(xul_verbose_mask_get(xul) & masks)) {
                        return;
                }
        }

        if (!xul->verbose->fp) {
                return;
        }

        g_fprintf(xul->verbose->fp, "[%.08lf] %s\n", xul_time0(xul), message);
        fflush(xul->verbose->fp);
}

XUL_APIEXPORT void
xul_verbose_filter_iso8601(const gchar * domain, xul_verbose_mask_e masks, const gchar * message,
                           gpointer __xul)
{
        xul_t *xul = (xul_t *) __xul;

        g_assert(XUL_IS_VALID(xul));

        if (masks != XUL_VERBOSE_MASK_0x0000) {
                if (!(xul_verbose_mask_get(xul) & masks)) {
                        return;
                }
        }

        if (!xul->verbose->fp) {
                return;
        }

        gchar buffer[256];

        g_fprintf(xul->verbose->fp, "%s\n", xul_time_iso8601_r(xul, buffer, sizeof(buffer)));
        fflush(xul->verbose->fp);

        g_fprintf(xul->verbose->fp, "%s\n", message);
        fflush(xul->verbose->fp);
}

XUL_APIEXPORT xul_verbose_filter_f
xul_verbose_filter_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul->verbose->filter;
}

XUL_APIEXPORT void
xul_verbose_filter_set(xul_t * xul, xul_verbose_filter_f filter)
{
        g_assert(XUL_IS_VALID(xul));

        g_log_set_handler(XUL_VERBOSE_DOMAIN, G_LOG_LEVEL_MASK, (GLogFunc) filter, xul);
}

XUL_APIEXPORT void
xul_verbose_log_close(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        if (!xul->verbose->fp) {
                return;
        }

        fclose(xul->verbose->fp);
}

XUL_APIEXPORT xul_rc_e
xul_verbose_log_open(xul_t * xul, const gchar * output)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_log_close(xul);

        xul->verbose->fp = g_fopen(output, "a+");

        if (xul->verbose->fp) {
                return XUL_SUCCESS;
        }

        xul_error_add(xul, XUL_ERROR, XUL_ERROR_FILEIO, "Unable to open %s: %s", output, g_strerror(errno));

        return XUL_FAILURE;
}

void
xul_verbose_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        g_free(verbose);
}

xul_verbose_t *
xul_verbose_alloc()
{
        xul_verbose_t *verbose = (xul_verbose_t *) g_malloc0(sizeof(xul_verbose_t));
        verbose->magic = XUL_VERBOSE_MAGIC;

        return verbose;
}

void
xul_verbose_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        xul_verbose_log_close(xul);

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

        xul_verbose_mask_set(xul, XUL_VERBOSE_MASK_0x0000);
        xul_verbose_filter_set(xul, xul_verbose_filter_time0);
        xul_verbose_log_open(xul, "/dev/stdout");
}

void
xul_log(xul_t * xul, const gchar * format, ...)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_t *verbose = xul->verbose;
        g_assert(XUL_VERBOSE_IS_VALID(verbose));

        va_list args;

        va_start(args, format);
        xul_verbose_log(format, args);
        va_end(args);
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
