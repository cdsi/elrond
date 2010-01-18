#ifndef XTIME_H
#define XTIME_H 1

/*
 * XUL Time Public API
 */

XUL_APIEXPORT gdouble xul_time(xul_t *, gdouble);
XUL_APIEXPORT gdouble xul_time0(xul_t *);
XUL_APIEXPORT gdouble xul_time_overhead(xul_t *);
XUL_APIEXPORT const gchar *xul_time_iso8601_r(xul_t *, gchar *, gsize);
XUL_APIEXPORT const gchar *xul_time_iso8601(xul_t *);

/*
 * XUL Time Private API
 */

void xul_time_delete(xul_t *);
xul_time_t *xul_time_new();
void xul_time_init(xul_t *);

#endif                          /* XTIME_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
