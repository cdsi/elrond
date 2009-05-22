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

XUL_APIEXPORT void
xul_prefs_close(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

XUL_APIEXPORT xul_rc_e
xul_prefs_open(xul_t * xul, const gchar * keyfile)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_raw_t *rawerror = NULL;

        if (g_key_file_load_from_file(xul->prefs->keyfile, keyfile, G_KEY_FILE_NONE, &rawerror)) {
                return XUL_SUCCESS;
        }

        g_prefix_error(&rawerror, "Unable to open %s: ", keyfile);

        xul_error_raw(xul, rawerror);

        return XUL_FAILURE;
}

void
xul_prefs_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_t *prefs = xul->prefs;
        g_assert(XUL_PREFS_IS_VALID(prefs));

        free(prefs);
}

xul_prefs_t *
xul_prefs_alloc()
{
        xul_prefs_t *prefs = (xul_prefs_t *) malloc(sizeof(xul_prefs_t));

        memset(prefs, 0, sizeof(xul_prefs_t));
        prefs->magic = XUL_PREFS_MAGIC;

        return prefs;
}

void
xul_prefs_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_t *prefs = xul->prefs;
        g_assert(XUL_PREFS_IS_VALID(prefs));

        g_key_file_free(prefs->keyfile);

        xul_prefs_free(xul);
}

xul_prefs_t *
xul_prefs_new()
{
        xul_prefs_t *prefs = xul_prefs_alloc();

        prefs->keyfile = g_key_file_new();

        return prefs;
}

void
xul_prefs_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_prefs_t *prefs = xul->prefs;
        g_assert(XUL_PREFS_IS_VALID(prefs));

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
