#include "common.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif                          /* HAVE_STDIO_H */

#if 0
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif                          /* HAVE_STDLIB_H */

#ifdef HAVE_STRING_H
#include <string.h>
#endif                          /* HAVE_STRING_H */
#endif

#include "xul.h"

int
main(int argc, char **argv)
{
        static gchar *backend = NULL;

        static GOptionEntry entries[] = {
                {"backend", 'b', 0, G_OPTION_ARG_STRING, &backend, "[emulated | hardware]", NULL},
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
