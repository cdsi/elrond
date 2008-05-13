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

        fprintf(xul->verbose->fp, "[%04d] %s\n", userdata->counter++, buffer);
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
                exit(1);
        }

        xul_t *xul = xul_init();

        xul_userdata_set(xul, (gpointer *) & userdata);

        const gchar *prefs = g_strconcat(getenv("ELROND_ETC"), G_DIR_SEPARATOR_S, "xultool.ini", NULL);

        xul_prefs_open(xul, prefs);

        guint32 iqvals = xul_prefs_guhex32_get(xul, "data", "iqvals");

        xul_verbose_log_0("iqvals = 0x%08X", iqvals);

        const gchar *output = g_strconcat(getenv("ELROND_LOG"), G_DIR_SEPARATOR_S, "xultool.log", NULL);

        xul_verbose_output_open(xul, output);

        xul_verbose_handler_set(xul, verbose_handler_redacted);
        xul_verbose_level_set(xul, xul_verbose_level_conv(xul, verbose));

        xul_verbose_log_5("ABCDEFGHIJKLMNOPQRSTUVWXYZ 0x%lX", (unsigned long)xul);

        xul_delete(xul);
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
