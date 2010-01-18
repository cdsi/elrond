#ifndef XVERBOSE_H
#define XVERBOSE_H 1

#define XUL_VERBOSE_DOMAIN "XUL"

/*
 * XUL Verbose Public API
 */

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
XUL_APIEXPORT void xul_verbose_filter_iso8601(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT xul_verbose_filter_f xul_verbose_filter_get(xul_t *);
XUL_APIEXPORT void xul_verbose_filter_set(xul_t *, xul_verbose_filter_f);
XUL_APIEXPORT void xul_verbose_log_close(xul_t *);
XUL_APIEXPORT xul_rc_e xul_verbose_log_open(xul_t *, const gchar *);

/*
 * XUL Verbose Private API
 */

void xul_verbose_delete(xul_t *);
xul_verbose_t *xul_verbose_new();
void xul_verbose_init(xul_t *);

#endif                          /* XVERBOSE_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
