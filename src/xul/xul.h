#ifndef XUL_H
#define XUL_H 1

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

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
        XUL_VERBOSE_MASK_0x0000 = G_LOG_LEVEL_DEBUG,
        XUL_VERBOSE_MASK_0x0001 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0000),
        XUL_VERBOSE_MASK_0x0002 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0001),
        XUL_VERBOSE_MASK_0x0004 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0002),
        XUL_VERBOSE_MASK_0x0008 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0003),
        XUL_VERBOSE_MASK_0x0010 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0004),
        XUL_VERBOSE_MASK_0x0020 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0005),
        XUL_VERBOSE_MASK_0x0040 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0006),
        XUL_VERBOSE_MASK_0x0080 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0007),
        XUL_VERBOSE_MASK_0x0100 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0008),
        XUL_VERBOSE_MASK_0x0200 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x0009),
        XUL_VERBOSE_MASK_0x0400 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000A),
        XUL_VERBOSE_MASK_0x0800 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000B),
        XUL_VERBOSE_MASK_0x1000 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000C),
        XUL_VERBOSE_MASK_0x2000 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000D),
        XUL_VERBOSE_MASK_0x4000 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000E),
        XUL_VERBOSE_MASK_0x8000 = 1 << (G_LOG_LEVEL_USER_SHIFT + 0x000F),
} xul_verbose_mask_e;

#define xul_verbose_filter_f GLogFunc

typedef struct {
        gboolean enabled;
        xul_verbose_mask_e mask;
        xul_verbose_filter_f filter;
        FILE *fp;
        guint32 magic;
} xul_verbose_t;

#define XUL_VERBOSE_MAGIC 0xDEADBABE
#define XUL_VERBOSE_IS_VALID(x) ((x) && ((x)->magic == XUL_VERBOSE_MAGIC))

typedef enum {
        XUL_SUCCESS = 0,
        XUL_FAILURE,
} xul_rc_e;

#define XUL_ERROR xul_error_domain_create("xul")

typedef enum {
        XUL_ERROR_FILEIO,       /* (f)open failed */
        XUL_ERROR_FAILED,       /* unexplained fatal error */
} xul_error_code_e;

typedef GError xul_error_raw_t;
typedef GQuark xul_error_domain_t;

typedef struct {
        xul_verbose_t *verbose;
        xul_error_raw_t *rawerror;
        guint32 magic;
} xul_error_t;

#define XUL_ERROR_MAGIC 0xABCDEFFE
#define XUL_ERROR_IS_VALID(x) ((x) && ((x)->magic == XUL_ERROR_MAGIC))

#define XUL_MAGIC 0xDEADBEEF
#define XUL_IS_VALID(x) ((x) && ((x)->magic == XUL_MAGIC))

#define XUL_APIEXPORT

/*
 * XUL Public API
 */

#include "_xul.h"

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
