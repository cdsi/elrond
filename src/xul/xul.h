#ifndef XUL_H
#define XUL_H 1

#include <glib.h>
#include <glib/gstdio.h>

#define XUL_MAGIC 0xDEADBEEF

typedef enum {
        XUL_SUCCESS = 0,
        XUL_ERROR = 1,
        XUL_EFOPEN = 2,
} xul_rc_e;

#define XUL_VERBOSE_DOMAIN "XUL"

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

#define xul_verbose_log_0(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_0, __VA_ARGS__)
#define xul_verbose_log_1(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_1, __VA_ARGS__)
#define xul_verbose_log_2(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_2, __VA_ARGS__)
#define xul_verbose_log_3(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_3, __VA_ARGS__)
#define xul_verbose_log_4(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_4, __VA_ARGS__)
#define xul_verbose_log_5(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_5, __VA_ARGS__)
#define xul_verbose_log_6(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_6, __VA_ARGS__)
#define xul_verbose_log_7(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_7, __VA_ARGS__)
#define xul_verbose_log_8(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_8, __VA_ARGS__)
#define xul_verbose_log_9(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_LEVEL_9, __VA_ARGS__)

#define xul_verbose_handler_f GLogFunc

typedef struct {
        xul_verbose_level_e level;
        xul_verbose_handler_f handler;
        FILE *fp;
} xul_verbose_t;

typedef struct {
        GKeyFile *keyfile;
} xul_prefs_t;

typedef struct {
        GTimeVal tv;
} xul_time_t;

typedef struct {
        guint32 magic;
        xul_rc_e rc;
        xul_verbose_t *verbose;
        xul_prefs_t *prefs;
        xul_time_t *time;
        gpointer *userdata;
} xul_t;

#define XUL_IS_VALID(x) ((x) && ((x)->magic == XUL_MAGIC))

#define XUL_IS_SUCCESS(x) ((x) && ((x)->rc == XUL_SUCCESS))

#define XUL_APIEXPORT

XUL_APIEXPORT xul_verbose_level_e xul_verbose_level_conv(xul_t *, gint);
XUL_APIEXPORT xul_verbose_level_e xul_verbose_level_get(xul_t *);
XUL_APIEXPORT void xul_verbose_level_set(xul_t *, xul_verbose_level_e);
XUL_APIEXPORT void xul_verbose_output_close(xul_t *);
XUL_APIEXPORT void xul_verbose_output_open(xul_t *, const gchar *);
XUL_APIEXPORT void xul_verbose_handler_default(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT xul_verbose_handler_f xul_verbose_handler_get(xul_t *);
XUL_APIEXPORT void xul_verbose_handler_set(xul_t *, xul_verbose_handler_f);
XUL_APIEXPORT void xul_prefs_close(xul_t *);
XUL_APIEXPORT void xul_prefs_open(xul_t *, const gchar *);
XUL_APIEXPORT guint32 xul_prefs_guint32_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_guint32_set(xul_t *, const gchar *, const gchar *, guint32);
XUL_APIEXPORT gdouble xul_xtime(xul_t *, gdouble);
XUL_APIEXPORT gdouble xul_xtime_overhead(xul_t *);
XUL_APIEXPORT gpointer *xul_userdata_get(xul_t *);
XUL_APIEXPORT void xul_userdata_set(xul_t *, gpointer *);
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
