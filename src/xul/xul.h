#ifndef XUL_H
#define XUL_H 1

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

typedef GByteArray xul_buffer_t;

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

#define XUL_ERROR_MAGIC 0xDEADCAFE
#define XUL_ERROR_IS_VALID(x) ((x) && ((x)->magic == XUL_ERROR_MAGIC))

#define XUL_ERROR xul_error_domain_create("xul")

#define XUL_HAS_ERROR(x) (XUL_IS_VALID(x) && XUL_ERROR_IS_VALID((x)->error) && (x)->error->rawerror)

typedef struct {
        GKeyFile *keyfile;
        guint32 magic;
} xul_prefs_t;

#define XUL_PREFS_MAGIC 0xBABEFACE
#define XUL_PREFS_IS_VALID(x) ((x) && ((x)->magic == XUL_PREFS_MAGIC))

typedef struct {
        guint8 *handle;
        const gchar *key;
        gsize size;
        guint32 magic;
} xul_shm_t;

#define XUL_SHM_MAGIC 0xF00DBABE
#define XUL_SHM_IS_VALID(x) ((x) && ((x)->magic == XUL_SHM_MAGIC))

typedef struct {
        GTimeVal tv;
        guint32 magic;
} xul_time_t;

#define XUL_TIME_MAGIC 0xBEEFBABE
#define XUL_TIME_IS_VALID(x) ((x) && ((x)->magic == XUL_TIME_MAGIC))

typedef GLogFunc xul_verbose_filter_f;

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

typedef struct {
        gboolean enabled;
        xul_verbose_mask_e mask;
        xul_verbose_filter_f filter;
        FILE *fp;
        guint32 magic;
} xul_verbose_t;

#define XUL_VERBOSE_MAGIC 0xDEADBABE
#define XUL_VERBOSE_IS_VALID(x) ((x) && ((x)->magic == XUL_VERBOSE_MAGIC))

#define XUL_VERBOSE_DOMAIN "XUL"

typedef struct {
        xul_prefs_t *prefs;
        xul_shm_t *shm;
        xul_time_t *time;
        xul_verbose_t *verbose;
        xul_error_t *error;
        gpointer *userdata;
        guint32 magic;
} xul_t;

#define XUL_MAGIC 0xDEADBEEF
#define XUL_IS_VALID(x) ((x) && ((x)->magic == XUL_MAGIC))

#define XUL_APIEXPORT

#include "_xul.h"

void xul_error_delete(xul_t *);
xul_error_t *xul_error_new();
void xul_error_init(xul_t *);

void xul_prefs_delete(xul_t *);
xul_prefs_t *xul_prefs_new();
void xul_prefs_init(xul_t *);

void xul_time_delete(xul_t *);
xul_time_t *xul_time_new();
void xul_time_init(xul_t *);

void xul_shm_delete(xul_t *);
xul_shm_t *xul_shm_new();
void xul_shm_init(xul_t *);

void xul_verbose_delete(xul_t *);
xul_verbose_t *xul_verbose_new();
void xul_verbose_init(xul_t *);

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
