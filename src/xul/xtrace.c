#include "elrond_common.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif                          /* HAVE_UNISTD_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

/*
 * Please see: http://www.gnome.org/~federico/news-2006-03.html#timeline-tools
 */

XUL_APIEXPORT void
xul_trace(xul_t * xul, const gchar * format, ...)
{
        g_assert(XUL_IS_VALID(xul));

        va_list args;
        gchar *formatted;
        gchar *cp;

        va_start(args, format);
        formatted = g_strdup_vprintf(format, args);
        va_end(args);

        cp = g_strdup_printf("MARK: %s: %s", g_get_prgname(), formatted);
        g_free(formatted);

        access(cp, F_OK);
        g_free(cp);
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
