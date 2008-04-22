#include "common.h"

#if 0
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif                          /* HAVE_STDLIB_H */

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif                          /* HAVE_STDIO_H */
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif                          /* HAVE_STRING_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

xul_t *
xul_alloc()
{
        xul_t *xul = (xul_t *) malloc(sizeof(xul_t));

        memset(xul, 0, sizeof(xul_t));
        xul->magic = XUL_MAGIC;

        return xul;
}

void
xul_free(xul_t * xul)
{
        if (!xul) {
                return;
        }

        free(xul);
}

XUL_APIEXPORT xul_t *
xul_init()
{
        xul_t *xul = xul_alloc();

        return xul;
}

XUL_APIEXPORT void
xul_delete(xul_t * xul)
{
        xul_free(xul);
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
