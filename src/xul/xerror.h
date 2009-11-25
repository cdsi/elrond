#ifndef XERROR_H
#define XERROR_H 1

#define XUL_IS_ERROR(x) (XUL_IS_VALID(x) && XUL_ERROR_IS_VALID((x)->error) && (x)->error->rawerror)

#define XUL_ERROR_VERBOSE_DOMAIN "XUL_ERROR"

/*
 * XUL Error Public API
 */

XUL_APIEXPORT xul_error_domain_t xul_error_domain_create(const gchar *);
XUL_APIEXPORT void xul_error_clear(xul_t *);
XUL_APIEXPORT void xul_error_raw(xul_t *, xul_error_raw_t *);
XUL_APIEXPORT void xul_error_add(xul_t *, xul_error_domain_t, xul_error_code_e, const gchar *, ...);
XUL_APIEXPORT const gchar *xul_error_message_get(xul_t *);

/*
 * XUL Error Private API
 */

void xul_error_delete(xul_t *);
xul_error_t *xul_error_new();
void xul_error_init(xul_t *);

#endif                          /* XERROR_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
