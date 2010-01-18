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

#include "xul.h"

#define XULTOOL_ERROR xul_error_domain_create("xultool")

#define xul_verbose_log_prefs xul_verbose_log_0x0001

typedef enum {
        XULTOOL_ERROR_FOO,
        XULTOOL_ERROR_BAR,
} xultool_error_e;

typedef struct {
        guint32 counter;
} userdata_t;

userdata_t userdata;

#define BUFFER_LENGTH 128

gchar g_buffer[BUFFER_LENGTH];

void
verbose_filter_redacted(const gchar * domain, GLogLevelFlags masks, const gchar * message, gpointer __xul)
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

        g_fprintf(stdout, "%s\n", message);
        fflush(stdout);

        gchar *buffer = g_strdup(message);

        for (int i = 0; buffer[i]; i++) {
                switch (g_ascii_toupper(buffer[i])) {
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                        buffer[i] = '.';
                        break;
                case 'Y':
                        if (!(i % 2)) {
                                buffer[i] = '.';
                        }
                        break;
                }
        }

        userdata_t *userdata = (userdata_t *) xul_userdata_get(xul);

        g_fprintf(xul->verbose->fp, "[%08" G_GINT32_MODIFIER "X] %s\n", userdata->counter++, buffer);
        fflush(xul->verbose->fp);

        g_free(buffer);
}

xul_rc_e
test_foo(xul_t * xul)
{
        xul_error_add(xul, XULTOOL_ERROR, XULTOOL_ERROR_FOO, "FOO FAILED");

        return XUL_FAILURE;
}

xul_rc_e
test_bar(xul_t * xul)
{
        xul_error_add(xul, XULTOOL_ERROR, XULTOOL_ERROR_BAR, "BAR FAILED");

        return XUL_FAILURE;
}

int
main(int argc, char **argv)
{
        static guint32 verbose = 0;

        static GOptionEntry entries[] = {
                {"verbose", 'v', 0, G_OPTION_ARG_INT, &verbose, "[0x0000..0xFFFF (default is 0)]", NULL},
                {NULL}
        };

        GOptionContext *context;
        GError *error = NULL;

        context = g_option_context_new("- tool to manipulate the xul");
        g_option_context_add_main_entries(context, entries, NULL);

        if (!g_option_context_parse(context, &argc, &argv, &error)) {
                g_fprintf(stderr, "ERROR: %s\n", error->message);
                return 1;
        }

        xul_t *xul = xul_new();
        xul_init(xul);

        gchar buffer[256];

        g_fprintf(stdout, "[%s]\n", xul_time_iso8601_r(xul, &buffer[0], sizeof(buffer)));

        xul_rc_e rc;

        xul_userdata_set(xul, (gpointer *) & userdata);

        xul_verbose_mask_set(xul, xul_verbose_mask_conv(xul, verbose));
        xul_verbose_filter_set(xul, verbose_filter_redacted);

        const gchar *output = g_strconcat(getenv("ELROND_LOG"), G_DIR_SEPARATOR_S, "xultool.log", NULL);

        rc = xul_verbose_log_open(xul, output);
        if (rc) {
                if (XUL_IS_ERROR(xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(xul));
                }
                return 1;
        }

        xul_verbose_log("verbose mask = 0x%0" G_GINT32_MODIFIER "X", verbose);

        const gchar *prefs = g_strconcat(getenv("ELROND_ETC"), G_DIR_SEPARATOR_S, "xultool.ini", NULL);

        rc = xul_prefs_open(xul, prefs);
        if (rc) {
                if (XUL_IS_ERROR(xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(xul));
                }
                return 1;
        }

        gint64 int64 = xul_prefs_gint64_get(xul, "data", "int64");
        xul_verbose_log_prefs("int64 = %" G_GINT64_FORMAT, int64);

        guint64 uint64 = xul_prefs_guint64_get(xul, "data", "uint64");
        xul_verbose_log_prefs("uint64 = %" G_GUINT64_FORMAT, uint64);

        gint32 int32 = xul_prefs_gint32_get(xul, "data", "int32");
        xul_verbose_log_prefs("int32 = %" G_GINT32_FORMAT, int32);

        guint32 uint32 = xul_prefs_guint32_get(xul, "data", "uint32");
        xul_verbose_log_prefs("uint32 = %" G_GUINT32_FORMAT, uint32);

        gint64 hex64 = xul_prefs_ghex64_get(xul, "data", "hex64");
        xul_verbose_log_prefs("hex64 = 0x%0" G_GINT64_MODIFIER "X", hex64);

        guint64 uhex64 = xul_prefs_guhex64_get(xul, "data", "uhex64");
        xul_verbose_log_prefs("uhex64 = 0x%0" G_GINT64_MODIFIER "X", uhex64);

        gint32 hex32 = xul_prefs_ghex32_get(xul, "data", "hex32");
        xul_verbose_log_prefs("hex32 = 0x%0" G_GINT32_MODIFIER "X", hex32);

        guint32 uhex32 = xul_prefs_guhex32_get(xul, "data", "uhex32");
        xul_verbose_log_prefs("uhex32 = 0x%0" G_GINT32_MODIFIER "X", uhex32);

        gdouble dubell = xul_prefs_gdouble_get(xul, "data", "double");
        xul_verbose_log_prefs("double = %lf", dubell);

        gboolean bool = xul_prefs_gboolean_get(xul, "data", "boolean");
        xul_verbose_log_prefs("boolean = %s", bool ? "TRUE" : "FALSE");

        const gchar *string = xul_prefs_gstring_get(xul, "data", "string", &g_buffer[0], sizeof(g_buffer));
        xul_verbose_log_prefs("string = %s", string);

        rc = test_foo(xul);
        if (rc) {
                if (XUL_IS_ERROR(xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(xul));
                        xul_error_clear(xul);
                }
        }

        rc = test_bar(xul);
        if (rc) {
                if (XUL_IS_ERROR(xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(xul));
                        xul_error_clear(xul);
                }
        }

        g_fprintf(stdout, "[%s]\n", xul_time_iso8601_r(xul, &buffer[0], sizeof(buffer)));

        xul_delete(xul);

        return 0;
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
