#ifndef XUL_H
#define XUL_H 1

#define XUL_MAGIC 0xDEADBEEF

typedef enum {
        XUL_SUCCESS = 0,
        XUL_ERROR = 1,
} xul_rc_e;

typedef struct {
        uint32_t magic;
        xul_rc_e rc;
} xul_t;

#define XUL_IS_VALID(x) (x->magic == XUL_MAGIC)

#define XUL_IS_SUCCESS(x) (x->rc == XUL_SUCCESS)

#define XUL_APIEXPORT

XUL_APIEXPORT xul_t *xul_init();
XUL_APIEXPORT void xul_delete(xul_t *);

#endif                          /* XUL_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
