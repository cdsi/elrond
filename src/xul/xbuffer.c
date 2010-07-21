#include "elrond_common.h"

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT void
xul_buffer_dump(xul_t * xul, xul_buffer_t * wrapper, const gchar * filename)
{
        g_assert(XUL_IS_VALID(xul));

        /* 
         * Assume that guint8 and gchar are the same size (i.e. nbytes is the same for both).
         */

        guint8 *buffer = xul_buffer_get_buffer(xul, wrapper);
        guint64 nbytes = xul_buffer_get_nbytes(xul, wrapper);

        g_file_set_contents(filename, (const gchar *)buffer, nbytes, NULL);
}

XUL_APIEXPORT guint64
xul_buffer_get_nbytes(xul_t * xul, xul_buffer_t * buffer)
{
        g_assert(XUL_IS_VALID(xul));

        guint64 nbytes = 0;

        if (buffer) {
                nbytes = buffer->len;
        }

        return nbytes;
}

XUL_APIEXPORT guint8 *
xul_buffer_get_buffer(xul_t * xul, xul_buffer_t * buffer)
{
        g_assert(XUL_IS_VALID(xul));

        return buffer->data;
}

XUL_APIEXPORT xul_buffer_t *
xul_buffer_append(xul_t * xul, xul_buffer_t * wrapper, const guint8 * buffer, guint64 nbytes)
{
        g_assert(XUL_IS_VALID(xul));

        return g_byte_array_append(wrapper, buffer, nbytes);
}

XUL_APIEXPORT void
xul_buffer_delete(xul_t * xul, xul_buffer_t * buffer)
{
        g_assert(XUL_IS_VALID(xul));

        g_byte_array_unref(buffer);
}

XUL_APIEXPORT xul_buffer_t *
xul_buffer_new_with_size(xul_t * xul, guint64 size)
{
        g_assert(XUL_IS_VALID(xul));

        return g_byte_array_sized_new(size);
}

XUL_APIEXPORT xul_buffer_t *
xul_buffer_new(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        return xul_buffer_new_with_size(xul, 1024 * 1024);
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
