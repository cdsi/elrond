typedef enum {
        XUL_SUCCESS = 0,
        XUL_FAILURE,
} xul_rc_e;

XUL_APIEXPORT gpointer *xul_userdata_get(xul_t *);
XUL_APIEXPORT void xul_userdata_set(xul_t *, gpointer *);
XUL_APIEXPORT void xul_delete(xul_t *);
XUL_APIEXPORT xul_t *xul_new();
XUL_APIEXPORT xul_rc_e xul_init(xul_t *);

XUL_APIEXPORT void xul_buffer_dump(xul_t *, xul_buffer_t *, const gchar *);
XUL_APIEXPORT guint64 xul_buffer_get_nbytes(xul_t *, xul_buffer_t *);
XUL_APIEXPORT guint8 *xul_buffer_get_buffer(xul_t *, xul_buffer_t *);
XUL_APIEXPORT xul_buffer_t *xul_buffer_append(xul_t *, xul_buffer_t *, const guint8 *, guint64);
XUL_APIEXPORT void xul_buffer_delete(xul_t *, xul_buffer_t *);
XUL_APIEXPORT xul_buffer_t *xul_buffer_new_with_nbytes(xul_t *, guint64);
XUL_APIEXPORT xul_buffer_t *xul_buffer_new(xul_t *);

XUL_APIEXPORT xul_error_domain_t xul_error_domain_create(const gchar *);
XUL_APIEXPORT void xul_error_clear(xul_t *);
XUL_APIEXPORT void xul_error_raw(xul_t *, xul_error_raw_t *);
XUL_APIEXPORT void xul_error_add(xul_t *, xul_error_domain_t, xul_error_code_e, const gchar *, ...);
XUL_APIEXPORT const gchar *xul_error_message_get(xul_t *);

XUL_APIEXPORT gint64 xul_prefs_gint64_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_gint64_set(xul_t *, const gchar *, const gchar *, gint64);
XUL_APIEXPORT guint64 xul_prefs_guint64_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_guint64_set(xul_t *, const gchar *, const gchar *, guint64);
XUL_APIEXPORT gint32 xul_prefs_gint32_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_gint32_set(xul_t *, const gchar *, const gchar *, gint32);
XUL_APIEXPORT guint32 xul_prefs_guint32_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_guint32_set(xul_t *, const gchar *, const gchar *, guint32);
XUL_APIEXPORT gint64 xul_prefs_ghex64_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_ghex64_set(xul_t *, const gchar *, const gchar *, gint64);
XUL_APIEXPORT guint64 xul_prefs_guhex64_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_guhex64_set(xul_t *, const gchar *, const gchar *, guint64);
XUL_APIEXPORT gint32 xul_prefs_ghex32_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_ghex32_set(xul_t *, const gchar *, const gchar *, gint32);
XUL_APIEXPORT guint32 xul_prefs_guhex32_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_guhex32_set(xul_t *, const gchar *, const gchar *, guint32);
XUL_APIEXPORT gdouble xul_prefs_gdouble_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_gdouble_set(xul_t *, const gchar *, const gchar *, gdouble);
XUL_APIEXPORT gboolean xul_prefs_gboolean_get(xul_t *, const gchar *, const gchar *);
XUL_APIEXPORT void xul_prefs_gboolean_set(xul_t *, const gchar *, const gchar *, gboolean);
XUL_APIEXPORT const gchar *xul_prefs_gstring_get(xul_t *, const gchar *, const gchar *, gchar *, gsize);
XUL_APIEXPORT void xul_prefs_gstring_set(xul_t *, const gchar *, const gchar *, const gchar *, gsize);
XUL_APIEXPORT void xul_prefs_close(xul_t *);
XUL_APIEXPORT xul_rc_e xul_prefs_open(xul_t *, const gchar *);

XUL_APIEXPORT void xul_shm_delete(xul_shm_t *);
XUL_APIEXPORT xul_shm_t *xul_shm_new(xul_t *);
XUL_APIEXPORT void xul_shm_init(xul_shm_t *);

XUL_APIEXPORT guint32 xul_shm_peek(xul_shm_t *, guint64);
XUL_APIEXPORT void xul_shm_poke(xul_shm_t *, guint64, guint32);

XUL_APIEXPORT void xul_shm_unmap(xul_shm_t *);
XUL_APIEXPORT xul_rc_e xul_shm_map(xul_shm_t *, const gchar *, guint64);

XUL_APIEXPORT gdouble xul_time(xul_t *, gdouble);
XUL_APIEXPORT gdouble xul_time0(xul_t *);
XUL_APIEXPORT gdouble xul_time_overhead(xul_t *);
XUL_APIEXPORT const gchar *xul_time_iso8601_r(xul_t *, gchar *, gsize);
XUL_APIEXPORT const gchar *xul_time_iso8601(xul_t *);

XUL_APIEXPORT void xul_trace(xul_t *, const gchar *, ...);

#define xul_verbose_log_0x0000(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0000, __VA_ARGS__)
#define xul_verbose_log_0x0001(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0001, __VA_ARGS__)
#define xul_verbose_log_0x0002(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0002, __VA_ARGS__)
#define xul_verbose_log_0x0004(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0004, __VA_ARGS__)
#define xul_verbose_log_0x0008(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0008, __VA_ARGS__)
#define xul_verbose_log_0x0010(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0010, __VA_ARGS__)
#define xul_verbose_log_0x0020(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0020, __VA_ARGS__)
#define xul_verbose_log_0x0040(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0040, __VA_ARGS__)
#define xul_verbose_log_0x0080(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0080, __VA_ARGS__)
#define xul_verbose_log_0x0100(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0100, __VA_ARGS__)
#define xul_verbose_log_0x0200(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0200, __VA_ARGS__)
#define xul_verbose_log_0x0400(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0400, __VA_ARGS__)
#define xul_verbose_log_0x0800(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x0800, __VA_ARGS__)
#define xul_verbose_log_0x1000(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x1000, __VA_ARGS__)
#define xul_verbose_log_0x2000(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x2000, __VA_ARGS__)
#define xul_verbose_log_0x4000(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x4000, __VA_ARGS__)
#define xul_verbose_log_0x8000(...) g_log(XUL_VERBOSE_DOMAIN, XUL_VERBOSE_MASK_0x8000, __VA_ARGS__)

#define xul_verbose_log xul_verbose_log_0x0000

XUL_APIEXPORT xul_verbose_mask_e xul_verbose_mask_conv(xul_t *, guint32);
XUL_APIEXPORT xul_verbose_mask_e xul_verbose_mask_get(xul_t *);
XUL_APIEXPORT void xul_verbose_mask_set(xul_t *, xul_verbose_mask_e);
XUL_APIEXPORT void xul_verbose_filter_default(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT void xul_verbose_filter_time0(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT void xul_verbose_filter_iso8601(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT xul_verbose_filter_f xul_verbose_filter_get(xul_t *);
XUL_APIEXPORT void xul_verbose_filter_set(xul_t *, xul_verbose_filter_f);
XUL_APIEXPORT void xul_verbose_log_close(xul_t *);
XUL_APIEXPORT xul_rc_e xul_verbose_log_open(xul_t *, const gchar *);
XUL_APIEXPORT void xul_log(xul_t *, const gchar *, ...);

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
