#include "elrond_common.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif                          /* HAVE_STDLIB_H */

#ifdef HAVE_MATH_H
#include <math.h>
#endif                          /* HAVE_MATH_H */

#include "xul.h"

#define BUFFER_LENGTH 128
gchar g_buffer[BUFFER_LENGTH];

static const gchar *g_quote =
  "A woman drove me to drink, and I didn't even have the decency to thank her. -- W.C. Fields";

xul_t *g_xul;

static void
test_xprefs_setup(void)
{
        g_xul = xul_new();
        g_assert(XUL_IS_VALID(g_xul));

        xul_init(g_xul);
}

static void
test_xprefs_teardown(void)
{
        g_assert(XUL_IS_VALID(g_xul));
        xul_delete(g_xul);
}

static void
test_xprefs(void)
{
        xul_rc_e rc;

        const gchar *prefs = g_strconcat(getenv("ELROND_ETC"), G_DIR_SEPARATOR_S, "xultest.ini", NULL);

        rc = xul_prefs_open(g_xul, prefs);
        g_assert(!rc);

        /* 
         * TODO: Test that the correct errors are raised when:
         *
         * 1. xultest.ini does not exist.
         * 2. xultest.ini is empty.
         * 3. getters cannot locate key/value pairs.
         * 4. numerical values overflow.
         *
         * For example 1 & 2 would be handled like:

         if (rc) {
         if (XUL_IS_ERROR(g_xul)) {
         g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(g_xul));
         }
         }

         */

        g_assert_cmpint(xul_prefs_gint64_get(g_xul, "xultest", "int64"), ==, pow(2, 62) * -1);
        g_assert_cmpuint(xul_prefs_guint64_get(g_xul, "xultest", "uint64"), ==, pow(2, 63));

        g_assert_cmpint(xul_prefs_gint32_get(g_xul, "xultest", "int32"), ==, pow(2, 30) * -1);
        g_assert_cmpuint(xul_prefs_guint32_get(g_xul, "xultest", "uint32"), ==, pow(2, 31));

        g_assert_cmphex(xul_prefs_ghex64_get(g_xul, "xultest", "hex64"), ==, 0x7ABECAFEBABECAFE);
        g_assert_cmphex(xul_prefs_guhex64_get(g_xul, "xultest", "uhex64"), ==, 0xDEADFACEDEADFACE);

        g_assert_cmphex(xul_prefs_ghex32_get(g_xul, "xultest", "hex32"), ==, 0x7ABECAFE);
        g_assert_cmphex(xul_prefs_guhex32_get(g_xul, "xultest", "uhex32"), ==, 0xDEADFACE);

        g_assert_cmpuint(xul_prefs_gboolean_get(g_xul, "xultest", "true"), ==, TRUE);
        g_assert_cmpuint(xul_prefs_gboolean_get(g_xul, "xultest", "false"), ==, FALSE);

        g_assert_cmpfloat(xul_prefs_gdouble_get(g_xul, "xultest", "double"), ==, 1234567890.0987654321);

        const gchar *string;

        string = xul_prefs_gstring_get(g_xul, "xultest", "string", &g_buffer[0], sizeof(g_buffer));

        g_assert_cmpstr(string, ==, g_quote);
        g_assert_cmpstr(string, ==, g_buffer);
}

GTestCase *
xul_test_xprefs_case(void)
{
        return g_test_create_case("xprefs", 0, NULL, test_xprefs_setup, test_xprefs, test_xprefs_teardown);
}

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
