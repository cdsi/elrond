#ifndef XVERBOSE_H
#define XVERBOSE_H 1

#define XUL_VERBOSE_DOMAIN "XUL"

/*
 * XUL Verbose Public API
 */

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

XUL_APIEXPORT xul_verbose_level_e xul_verbose_level_conv(xul_t *, gint);
XUL_APIEXPORT xul_verbose_level_e xul_verbose_level_get(xul_t *);
XUL_APIEXPORT void xul_verbose_level_set(xul_t *, xul_verbose_level_e);
XUL_APIEXPORT void xul_verbose_output_close(xul_t *);
XUL_APIEXPORT void xul_verbose_output_open(xul_t *, const gchar *);
XUL_APIEXPORT void xul_verbose_handler_default(const gchar *, GLogLevelFlags, const gchar *, gpointer);
XUL_APIEXPORT xul_verbose_handler_f xul_verbose_handler_get(xul_t *);
XUL_APIEXPORT void xul_verbose_handler_set(xul_t *, xul_verbose_handler_f);

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
