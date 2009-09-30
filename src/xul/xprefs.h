#ifndef XPREFS_H
#define XPREFS_H 1

/*
 * XUL Prefs Public API
 */

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

/*
 * XUL Prefs Private API
 */

void xul_prefs_delete(xul_t *);
xul_prefs_t *xul_prefs_new();
void xul_prefs_init(xul_t *);

#endif                          /* XPREFS_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
