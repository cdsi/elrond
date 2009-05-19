#ifndef XUL_H
#define XUL_H 1

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

typedef gboolean xul_rc_t;

#define XUL_SUCCESS FALSE
#define XUL_FAILURE TRUE

#define XUL_ERROR xul_error_domain_create("xul")

typedef enum {
        XUL_ERROR_FILEIO,       /* (f)open failed */
        XUL_ERROR_FAILED,       /* unexplained fatal error */
} xul_error_code_e;

typedef GError xul_error_raw_t;
typedef GQuark xul_error_domain_t;

typedef struct {
        xul_error_raw_t *rawerror;
        guint32 magic;
} xul_error_t;

#define XUL_ERROR_MAGIC 0xABCDEFFE
#define XUL_ERROR_IS_VALID(x) ((x) && ((x)->magic == XUL_ERROR_MAGIC))

typedef struct {
        GKeyFile *keyfile;
        guint32 magic;
} xul_prefs_t;

#define XUL_PREFS_MAGIC 0xBABEFACE
#define XUL_PREFS_IS_VALID(x) ((x) && ((x)->magic == XUL_PREFS_MAGIC))

typedef struct {
        GTimeVal tv;
        guint32 magic;
} xul_time_t;

#define XUL_TIME_MAGIC 0xBEEFBABE
#define XUL_TIME_IS_VALID(x) ((x) && ((x)->magic == XUL_TIME_MAGIC))

typedef enum {
        XUL_VERBOSE_LEVEL_0 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0),
        XUL_VERBOSE_LEVEL_1 = 1 << (G_LOG_LEVEL_USER_SHIFT + 1),
        XUL_VERBOSE_LEVEL_2 = 1 << (G_LOG_LEVEL_USER_SHIFT + 2),
        XUL_VERBOSE_LEVEL_3 = 1 << (G_LOG_LEVEL_USER_SHIFT + 3),
        XUL_VERBOSE_LEVEL_4 = 1 << (G_LOG_LEVEL_USER_SHIFT + 4),
        XUL_VERBOSE_LEVEL_5 = 1 << (G_LOG_LEVEL_USER_SHIFT + 5),
        XUL_VERBOSE_LEVEL_6 = 1 << (G_LOG_LEVEL_USER_SHIFT + 6),
        XUL_VERBOSE_LEVEL_7 = 1 << (G_LOG_LEVEL_USER_SHIFT + 7),
        XUL_VERBOSE_LEVEL_8 = 1 << (G_LOG_LEVEL_USER_SHIFT + 8),
        XUL_VERBOSE_LEVEL_9 = 1 << (G_LOG_LEVEL_USER_SHIFT + 9),
} xul_verbose_level_e;

#define xul_verbose_handler_f GLogFunc

typedef struct {
        xul_verbose_level_e level;
        xul_verbose_handler_f handler;
        FILE *fp;
        guint32 magic;
} xul_verbose_t;

#define XUL_VERBOSE_MAGIC 0xDEADBABE
#define XUL_VERBOSE_IS_VALID(x) ((x) && ((x)->magic == XUL_VERBOSE_MAGIC))

typedef struct {
        xul_error_t *error;
        xul_prefs_t *prefs;
        xul_time_t *time;
        xul_verbose_t *verbose;
        gpointer *userdata;
        guint32 magic;
} xul_t;

#define XUL_MAGIC 0xDEADBEEF
#define XUL_IS_VALID(x) ((x) && ((x)->magic == XUL_MAGIC))

#define XUL_APIEXPORT

/*
 * XUL Public API
 */

XUL_APIEXPORT gpointer *xul_userdata_get(xul_t *);
XUL_APIEXPORT void xul_userdata_set(xul_t *, gpointer *);
XUL_APIEXPORT void xul_delete(xul_t *);
XUL_APIEXPORT xul_t *xul_new();
XUL_APIEXPORT void xul_init(xul_t *);

#include "xerror.h"
#include "xprefs.h"
#include "xtime.h"
#include "xtrace.h"
#include "xverbose.h"

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
