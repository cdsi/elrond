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
xul_shm_peek(xul_shm_t * shm, guint64 offset)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        return *(guint32 *) (shm->addr + offset);
}

XUL_APIEXPORT void
xul_shm_poke(xul_shm_t * shm, guint64 offset, guint32 data)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        *(guint32 *) (shm->addr + offset) = data;
}

XUL_APIEXPORT void
xul_shm_unmap(xul_shm_t * shm)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        /* NOOP */
}

XUL_APIEXPORT xul_rc_e
xul_shm_map(xul_shm_t * shm, const gchar * key, guint64 memsize)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        /* TODO: use glib routine to obtain pid */
        shm->memname = g_strdup_printf("/%s-%" G_GUINT64_FORMAT, key, (guint64) getpid());

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
xul_shm_free(xul_shm_t * shm)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        g_free(shm->memname);
        g_free(shm);
}

xul_shm_t *
xul_shm_alloc()
{
        xul_shm_t *shm = (xul_shm_t *) g_malloc0(sizeof(xul_shm_t));
        shm->magic = XUL_SHM_MAGIC;

        return shm;
}

XUL_APIEXPORT void
xul_shm_delete(xul_shm_t * shm)
{
        g_assert(XUL_SHM_IS_VALID(shm));

        xul_t *xul = shm->xul;
        g_assert(XUL_IS_VALID(xul));

        xul_shm_unmap(shm);
        xul_shm_free(shm);
}

XUL_APIEXPORT xul_shm_t *
xul_shm_new(xul_t * xul)
{
        g_assert(XUL_IS_VALID(xul));

        xul_shm_t *shm = xul_shm_alloc();
        shm->xul = xul;

        return shm;
}

XUL_APIEXPORT void
xul_shm_init(xul_shm_t * shm)
{
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
