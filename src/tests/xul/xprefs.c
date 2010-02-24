#include "elrond_common.h"

#include "xul.h"

xul_t *g_xul;

static void
test_xprefs_setup(void)
{
        g_xul = xul_new();
        g_assert(XUL_IS_VALID(g_xul));
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
