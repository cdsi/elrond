typedef struct {
        xul_prefs_t *prefs;
        xul_time_t *time;
        xul_verbose_t *verbose;
        xul_error_t *error;
        gpointer *userdata;
        guint32 magic;
} xul_t;

XUL_APIEXPORT gpointer *xul_userdata_get(xul_t *);
XUL_APIEXPORT void xul_userdata_set(xul_t *, gpointer *);
XUL_APIEXPORT void xul_delete(xul_t *);
XUL_APIEXPORT xul_t *xul_new();
XUL_APIEXPORT void xul_init(xul_t *);

typedef GByteArray xul_buffer_t;

XUL_APIEXPORT guint64 xul_buffer_get_length(xul_t *, xul_buffer_t *);
XUL_APIEXPORT guint8 *xul_buffer_get_data(xul_t *, xul_buffer_t *);
XUL_APIEXPORT xul_buffer_t *xul_buffer_append(xul_t *, xul_buffer_t *, const guint8 *, guint64);
XUL_APIEXPORT void xul_buffer_delete(xul_t *, xul_buffer_t *);
XUL_APIEXPORT xul_buffer_t *xul_buffer_new_with_size(xul_t *, guint64);
XUL_APIEXPORT xul_buffer_t *xul_buffer_new(xul_t *);

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
