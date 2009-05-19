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

APIEXPORT xul_error_domain_t
xul_error_domain_create(const gchar * name)
{
        return g_quark_from_static_string(name);
}

APIEXPORT void
xul_error_clear(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        g_clear_error(&error->rawerror);
}

APIEXPORT void
xul_error_add_raw(xul_t * xul, xul_error_raw_t * rawerror)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        if (!error->rawerror) {
                error->rawerror = rawerror;
        }
        else {
                /* 
                 * This situation should be avoided. Errors should be handled, or
                 * immediately passed back to the caller.
                 */
                g_propagate_error(&error->rawerror, rawerror);
        }
}

APIEXPORT void
xul_error_add(xul_t * xul, xul_error_domain_t domain, xul_error_code_e code, const gchar * format, ...)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        va_list args;
        gchar *formatted;

        va_start(args, format);
        formatted = g_strdup_vprintf(format, args);
        va_end(args);

        xul_error_raw_t *rawerror = g_error_new_literal(domain, code, formatted);

        g_free(formatted);

        xul_error_add_raw(xul, rawerror);
}

APIEXPORT const gchar *
xul_error_message_get(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        if (error->rawerror) {
                return error->rawerror->message;
        }

        return NULL;
}

void
xul_error_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        free(error);
}

xul_error_t *
xul_error_alloc()
{
        xul_error_t *error = (xul_error_t *) malloc(sizeof(xul_error_t));

        memset(error, 0, sizeof(xul_error_t));
        error->magic = XUL_ERROR_MAGIC;

        return error;
}

void
xul_error_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));

        xul_error_clear(xul);
        xul_error_free(xul);
}

xul_error_t *
xul_error_new()
{
        xul_error_t *error = xul_error_alloc();

        return error;
}

void
xul_error_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_error_t *error = xul->error;
        g_assert(XUL_ERROR_IS_VALID(error));
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
