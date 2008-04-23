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

void
verbose_handler_redacted(const gchar * domain, GLogLevelFlags level, const gchar * message, gpointer data)
{
        xul_t *xul = (xul_t *) data;

        g_assert(XUL_IS_VALID(xul));

        if (xul->verbose->level < level) {
                return;
        }

        gchar *buffer = g_strdup(message);

        for (int i = 0; buffer[i] != '\0'; i++) {
                switch (g_ascii_toupper(buffer[i])) {
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                case 'Y':
                        buffer[i] = '.';
                        break;
                }
        }

        fprintf(xul->verbose->fp, "%s\n", buffer);
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

        GError *error = NULL;
        GOptionContext *context;

        context = g_option_context_new("- tool to manipulate the xul");
        g_option_context_add_main_entries(context, entries, NULL);

        if (!g_option_context_parse(context, &argc, &argv, &error)) {
                fprintf(stderr, "ERROR: %s\n", error->message);
                exit(1);
        }

        xul_t *xul = xul_init();

        xul_verbose_handler_set(xul, xul_verbose_handler_default);
        xul_verbose_output_open(xul, "/dev/stdout");

        xul_verbose_level_set(xul, XUL_VERBOSE_LEVEL_0);
        xul_verbose_log_0("ABCDEFGHIJKLMNOPQRSTUVWXYZ 0x%lX", (unsigned long)xul);

        xul_verbose_handler_set(xul, verbose_handler_redacted);
        xul_verbose_output_open(xul, "/dev/stderr");

        xul_verbose_level_set(xul, xul_verbose_level_conv(xul, verbose));
        xul_verbose_log_5("ABCDEFGHIJKLMNOPQRSTUVWXYZ 0x%lX", (unsigned long)xul);

        xul_verbose_handler_set(xul, xul_verbose_handler_default);
        xul_verbose_output_open(xul, "xultool.log");

        xul_verbose_level_set(xul, XUL_VERBOSE_LEVEL_0);
        xul_verbose_log_0("ABCDEFGHIJKLMNOPQRSTUVWXYZ 0x%lX", (unsigned long)xul);

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
