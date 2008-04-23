#ifndef XUL_H
#define XUL_H 1

#include <stdint.h>
#include <glib.h>

#define XUL_MAGIC 0xDEADBEEF

typedef enum {
        XUL_SUCCESS = 0,
        XUL_ERROR = 1,
        XUL_EFOPEN = 2,
} xul_rc_e;

typedef struct {
        uint32_t level;
        FILE *fp;
} xul_verbose_t;

typedef struct {
        uint32_t magic;
        xul_rc_e rc;
        xul_verbose_t *verbose;
} xul_t;

#define XUL_IS_VALID(x) ((x) && ((x)->magic == XUL_MAGIC))

#define XUL_IS_SUCCESS(x) ((x) && ((x)->rc == XUL_SUCCESS))

#define XUL_VERBOSE_LEVEL_ERROR G_LOG_LEVEL_ERROR
#define XUL_VERBOSE_LEVEL_CRITICAL G_LOG_LEVEL_CRITICAL
#define XUL_VERBOSE_LEVEL_WARNING G_LOG_LEVEL_WARNING
#define XUL_VERBOSE_LEVEL_MESSAGE G_LOG_LEVEL_MESSAGE
#define XUL_VERBOSE_LEVEL_INFO G_LOG_LEVEL_INFO
#define XUL_VERBOSE_LEVEL_DEBUG G_LOG_LEVEL_DEBUG

#define xul_verbose_message g_message
#define xul_verbose_warning g_warning
#define xul_verbose_critical g_critical
#define xul_verbose_error g_error
#define xul_verbose_debug g_debug

#define XUL_APIEXPORT

XUL_APIEXPORT xul_t *xul_init();
XUL_APIEXPORT void xul_delete(xul_t *);
XUL_APIEXPORT int32_t xul_verbose_level_get(xul_t *);
XUL_APIEXPORT void xul_verbose_level_set(xul_t *, int32_t);
XUL_APIEXPORT void xul_verbose_output_open(xul_t *, const char *);
XUL_APIEXPORT void xul_verbose_output_close(xul_t *);

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
