#include "elrond_common.h"

#include <fcntl.h>
#include <sys/mman.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif                          /* HAVE_UNISTD_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT void
xul_shm_unmap(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));
}

XUL_APIEXPORT xul_rc_e
xul_shm_map(xul_t * xul, const gchar * key, guint64 size)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        shm->handle = NULL;

        gchar *filename = g_strdup_printf("/dev/shm/%s", key);

        int fd = g_open(filename, O_RDWR);
        if (fd != -1) {
                shm->handle = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        }

        g_free(filename);
        close(fd);

        return shm->handle ? XUL_SUCCESS : XUL_ERROR;
}

void
xul_shm_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *xshm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(xshm));

        g_free(xshm);
}

xul_shm_t *
xul_shm_alloc()
{
        xul_shm_t *xshm = (xul_shm_t *) g_malloc0(sizeof(xul_shm_t));
        xshm->magic = XUL_SHM_MAGIC;

        return xshm;
}

void
xul_shm_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *xshm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(xshm));

        xul_shm_free(xul);
}

xul_shm_t *
xul_shm_new()
{
        xul_shm_t *xshm = xul_shm_alloc();

        return xshm;
}

void
xul_shm_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *xshm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(xshm));

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
