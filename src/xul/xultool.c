#include "common.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif                          /* HAVE_STDIO_H */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif                          /* HAVE_STDLIB_H */

#ifdef HAVE_STRING_H
#include <string.h>
#endif                          /* HAVE_STRING_H */

#include <glib.h>
#include <glib/gprintf.h>

#include "xul.h"

typedef struct {
        gint32 counter;
} userdata_t;

userdata_t userdata;

void
verbose_handler_redacted(const gchar * domain, GLogLevelFlags level, const gchar * message, gpointer __xul)
{
        xul_t *xul = (xul_t *) __xul;

        g_assert(XUL_IS_VALID(xul));

        if (xul_verbose_level_get(xul) < level) {
                return;
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

        g_fprintf(xul->verbose->fp, "[%04X] %s\n", userdata->counter++, buffer);
        fflush(xul->verbose->fp);

        free(buffer);
}

int
main(int argc, char **argv)
{
        static gint verbose = 0;

        static GOptionEntry entries[] = {
                {"verbose", 'v', 0, G_OPTION_ARG_INT, &verbose, "[0..9 (default is 0)]", NULL},
                {NULL}
        };

        GOptionContext *context;
        GError *error = NULL;

        context = g_option_context_new("- tool to manipulate the xul");
        g_option_context_add_main_entries(context, entries, NULL);

        if (!g_option_context_parse(context, &argc, &argv, &error)) {
                fprintf(stderr, "ERROR: %s\n", error->message);
                return 1;
        }

        xul_t *xul = xul_init();

        xul_userdata_set(xul, (gpointer *) & userdata);

        const gchar *output = g_strconcat(getenv("ELROND_LOG"), G_DIR_SEPARATOR_S, "xultool.log", NULL);

        xul_verbose_output_open(xul, output);

        xul_verbose_handler_set(xul, verbose_handler_redacted);
        xul_verbose_level_set(xul, xul_verbose_level_conv(xul, verbose));

        const gchar *prefs = g_strconcat(getenv("ELROND_ETC"), G_DIR_SEPARATOR_S, "xultool.ini", NULL);

        xul_prefs_open(xul, prefs);

        gint64 int64 = xul_prefs_guint64_get(xul, "data", "int64");
        xul_verbose_log_0("int64 = %" PRId64, int64);

        guint64 uint64 = xul_prefs_guint64_get(xul, "data", "uint64");
        xul_verbose_log_0("uint64 = %" PRIu64, uint64);

        gint32 int32 = xul_prefs_guint32_get(xul, "data", "int32");
        xul_verbose_log_0("int32 = %" PRId32, int32);

        guint32 uint32 = xul_prefs_guint32_get(xul, "data", "uint32");
        xul_verbose_log_0("uint32 = %" PRIu32, uint32);

        gint64 hex64 = xul_prefs_guhex64_get(xul, "data", "hex64");
        xul_verbose_log_0("hex64 = 0x%08" PRIX64, hex64);

        guint64 uhex64 = xul_prefs_guhex64_get(xul, "data", "uhex64");
        xul_verbose_log_0("uhex64 = 0x%08" PRIX64, uhex64);

        gint32 hex32 = xul_prefs_guhex32_get(xul, "data", "hex32");
        xul_verbose_log_0("hex32 = 0x%08" PRIX32, hex32);

        guint32 uhex32 = xul_prefs_guhex32_get(xul, "data", "uhex32");
        xul_verbose_log_0("uhex32 = 0x%08" PRIX32, uhex32);

        gdouble dubell = xul_prefs_gdouble_get(xul, "data", "double");
        xul_verbose_log_0("double = %lf", dubell);

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
