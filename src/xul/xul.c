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

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

/*
 * XUL Verbose API
 */

XUL_APIEXPORT xul_verbose_level_e
xul_verbose_level_conv(xul_t * xul, gint verbose)
{
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

        xul->rc = XUL_SUCCESS;
}

XUL_APIEXPORT void
xul_verbose_output_open(xul_t * xul, const gchar * output)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_output_close(xul);

        xul->verbose->fp = g_fopen(output, "a+");

        if (!xul->verbose->fp) {
                xul->rc = XUL_EFOPEN;
                return;
        }

        xul->rc = XUL_SUCCESS;
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
verbose_free(xul_verbose_t * verbose)
{
        free(verbose);
}

xul_verbose_t *
verbose_alloc()
{
        xul_verbose_t *verbose = (xul_verbose_t *) malloc(sizeof(xul_verbose_t));

        memset(verbose, 0, sizeof(xul_verbose_t));
        verbose->level = XUL_VERBOSE_LEVEL_0;

        return verbose;
}

void
verbose_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_output_close(xul);
}

void
verbose_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_verbose_handler_set(xul, xul_verbose_handler_default);
        xul_verbose_level_set(xul, XUL_VERBOSE_LEVEL_0);
        xul_verbose_output_open(xul, "/dev/stdout");
}

/*
 * XUL Prefs API
 */

XUL_APIEXPORT void
xul_prefs_close(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

XUL_APIEXPORT void
xul_prefs_open(xul_t * xul, const gchar * keyfile)
{
        g_assert(XUL_IS_VALID(xul));

        GError *error = NULL;

        if (!g_key_file_load_from_file(xul->prefs->keyfile, keyfile, G_KEY_FILE_NONE, &error)) {
                xul->rc = XUL_ERROR;
                return;
        }

        xul->rc = XUL_SUCCESS;
}

XUL_APIEXPORT gint64
xul_prefs_gint64_get(xul_t * xul, const gchar * group, const gchar * key)
{
        g_assert(XUL_IS_VALID(xul));

        return g_ascii_strtoll(g_key_file_get_string(xul->prefs->keyfile, group, key, NULL), NULL, 10);
}

XUL_APIEXPORT void
xul_prefs_gint64_set(xul_t * xul, const gchar * group, const gchar * key, gint64 value)
{
        g_assert(XUL_IS_VALID(xul));

        gchar buffer[64];

        g_snprintf(buffer, sizeof(buffer), "%" G_GINT64_FORMAT, value);

        g_key_file_set_string(xul->prefs->keyfile, group, key, buffer);
}

XUL_APIEXPORT guint64
xul_prefs_guint64_get(xul_t * xul, const gchar * group, const gchar * key)
{
        g_assert(XUL_IS_VALID(xul));

        return g_ascii_strtoull(g_key_file_get_string(xul->prefs->keyfile, group, key, NULL), NULL, 10);
}

XUL_APIEXPORT void
xul_prefs_guint64_set(xul_t * xul, const gchar * group, const gchar * key, guint64 value)
{
        g_assert(XUL_IS_VALID(xul));

        gchar buffer[64];

        g_snprintf(buffer, sizeof(buffer), "%" G_GUINT64_FORMAT, value);

        g_key_file_set_string(xul->prefs->keyfile, group, key, buffer);
}

XUL_APIEXPORT gint32
xul_prefs_gint32_get(xul_t * xul, const gchar * group, const gchar * key)
{
        return (gint32) xul_prefs_gint64_get(xul, group, key);
}

XUL_APIEXPORT void
xul_prefs_gint32_set(xul_t * xul, const gchar * group, const gchar * key, gint32 value)
{
        xul_prefs_gint64_set(xul, group, key, (gint64) value);
}

XUL_APIEXPORT guint32
xul_prefs_guint32_get(xul_t * xul, const gchar * group, const gchar * key)
{
        return (guint32) xul_prefs_guint64_get(xul, group, key);
}

XUL_APIEXPORT void
xul_prefs_guint32_set(xul_t * xul, const gchar * group, const gchar * key, guint32 value)
{
        xul_prefs_guint64_set(xul, group, key, (guint64) value);
}

XUL_APIEXPORT gint64
xul_prefs_ghex64_get(xul_t * xul, const gchar * group, const gchar * key)
{
        g_assert(XUL_IS_VALID(xul));

        return g_ascii_strtoll(g_key_file_get_string(xul->prefs->keyfile, group, key, NULL), NULL, 16);
}

XUL_APIEXPORT void
xul_prefs_ghex64_set(xul_t * xul, const gchar * group, const gchar * key, gint64 value)
{
        g_assert(XUL_IS_VALID(xul));

        gchar buffer[64];

        g_snprintf(buffer, sizeof(buffer), "0x%0" G_GINT64_MODIFIER "X", value);

        g_key_file_set_string(xul->prefs->keyfile, group, key, buffer);
}

XUL_APIEXPORT guint64
xul_prefs_guhex64_get(xul_t * xul, const gchar * group, const gchar * key)
{
        g_assert(XUL_IS_VALID(xul));

        return g_ascii_strtoull(g_key_file_get_string(xul->prefs->keyfile, group, key, NULL), NULL, 16);
}

XUL_APIEXPORT void
xul_prefs_guhex64_set(xul_t * xul, const gchar * group, const gchar * key, guint64 value)
{
        g_assert(XUL_IS_VALID(xul));

        gchar buffer[64];

        g_snprintf(buffer, sizeof(buffer), "0x%0" G_GINT64_MODIFIER "X", value);

        g_key_file_set_string(xul->prefs->keyfile, group, key, buffer);
}

XUL_APIEXPORT gint32
xul_prefs_ghex32_get(xul_t * xul, const gchar * group, const gchar * key)
{
        return (gint32) xul_prefs_ghex64_get(xul, group, key);
}

XUL_APIEXPORT void
xul_prefs_ghex32_set(xul_t * xul, const gchar * group, const gchar * key, gint32 value)
{
        xul_prefs_ghex64_set(xul, group, key, (gint64) value);
}

XUL_APIEXPORT guint32
xul_prefs_guhex32_get(xul_t * xul, const gchar * group, const gchar * key)
{
        return (guint32) xul_prefs_guhex64_get(xul, group, key);
}

XUL_APIEXPORT void
xul_prefs_guhex32_set(xul_t * xul, const gchar * group, const gchar * key, guint32 value)
{
        xul_prefs_guhex64_set(xul, group, key, (guint64) value);
}

XUL_APIEXPORT gdouble
xul_prefs_gdouble_get(xul_t * xul, const gchar * group, const gchar * key)
{
        g_assert(XUL_IS_VALID(xul));

        return g_key_file_get_double(xul->prefs->keyfile, group, key, NULL);
}

XUL_APIEXPORT void
xul_prefs_gdouble_set(xul_t * xul, const gchar * group, const gchar * key, gdouble value)
{
        g_assert(XUL_IS_VALID(xul));

        g_key_file_set_double(xul->prefs->keyfile, group, key, value);
}

void
prefs_free(xul_prefs_t * prefs)
{
        g_key_file_free(prefs->keyfile);
        free(prefs);
}

xul_prefs_t *
prefs_alloc()
{
        xul_prefs_t *prefs = (xul_prefs_t *) malloc(sizeof(xul_prefs_t));

        memset(prefs, 0, sizeof(xul_prefs_t));
        prefs->keyfile = g_key_file_new();

        return prefs;
}

void
prefs_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_close(xul);
}

void
prefs_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

/*
 * XUL Time API
 */

void
time_free(xul_time_t * time)
{
        free(time);
}

xul_time_t *
time_alloc()
{
        xul_time_t *time = (xul_time_t *) malloc(sizeof(xul_time_t));

        memset(time, 0, sizeof(xul_time_t));

        return time;
}

void
time_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

void
time_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

/*
 * XUL API
 */

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

        verbose_free(xul->verbose);
        prefs_free(xul->prefs);
        time_free(xul->time);

        free(xul);
}

xul_t *
xul_alloc()
{
        xul_t *xul = (xul_t *) malloc(sizeof(xul_t));

        memset(xul, 0, sizeof(xul_t));
        xul->magic = XUL_MAGIC;

        xul->verbose = verbose_alloc();
        xul->prefs = prefs_alloc();
        xul->time = time_alloc();

        return xul;
}

XUL_APIEXPORT void
xul_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        verbose_delete(xul);
        prefs_delete(xul);
        time_delete(xul);

        xul_free(xul);
}

XUL_APIEXPORT xul_t *
xul_init()
{
        xul_t *xul = xul_alloc();

        verbose_init(xul);
        prefs_init(xul);
        time_init(xul);

        return xul;
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
