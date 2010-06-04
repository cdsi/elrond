#include "elrond_common.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#ifdef HAVE_STRING_H
#include <string.h>
#endif                          /* HAVE_UNISTD_H */

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif                          /* HAVE_UNISTD_H */

#define XUL_EXPORT_SYMBOLS 1
#include "xul.h"

XUL_APIEXPORT guint32
xul_shm_peek(xul_t * xul, guint64 offset)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

        return *(guint32 *) (shm->addr + offset);
}

XUL_APIEXPORT void
xul_shm_poke(xul_t * xul, guint64 offset, guint32 data)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

        *(guint32 *) (shm->addr + offset) = data;
}

XUL_APIEXPORT void
xul_shm_unmap(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

        if (shm->addr) {
                g_free(shm->memname);
        }

        shm->addr = NULL;
}

XUL_APIEXPORT xul_rc_e
xul_shm_map(xul_t * xul, const gchar * key, guint64 memsize)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        shm->addr = NULL;

        shm->memname = g_strdup_printf("/%s", key);

        int fd = shm_open(shm->memname, O_CREAT | O_RDWR, 0600);
        if (fd == -1) {
                xul_error_add(xul, XUL_ERROR, XUL_ERROR_SHMEM,
                              g_strdup_printf("%s:%d:xul_shm_map: %s", __FILE__, __LINE__, strerror(errno)));
                return XUL_ERROR;
        }

        ftruncate(fd, memsize);

        shm->addr = mmap(NULL, memsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (shm->addr == MAP_FAILED) {
                xul_error_add(xul, XUL_ERROR, XUL_ERROR_SHMEM,
                              g_strdup_printf("%s:%d:xul_shm_map: %s", __FILE__, __LINE__, strerror(errno)));
                return XUL_ERROR;
        }

        close(fd);

        return XUL_SUCCESS;
}

void
xul_shm_free(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

        g_free(shm);
}

xul_shm_t *
xul_shm_alloc()
{
        xul_shm_t *shm = (xul_shm_t *) g_malloc0(sizeof(xul_shm_t));
        shm->magic = XUL_SHM_MAGIC;

        return shm;
}

void
xul_shm_delete(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_shm_unmap(xul);

        xul_shm_free(xul);
}

xul_shm_t *
xul_shm_new()
{
        xul_shm_t *shm = xul_shm_alloc();

        return shm;
}

void
xul_shm_init(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul->shm;
        g_assert(XUL_SHM_IS_VALID(shm));

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
