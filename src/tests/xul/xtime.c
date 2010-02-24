#include "elrond_common.h"

#include "xul.h"

xul_t *g_xul;

static void
test_xtime_setup(void)
{
        g_xul = xul_new();
        g_assert(XUL_IS_VALID(g_xul));
}

static void
test_xtime_teardown(void)
{
        g_assert(XUL_IS_VALID(g_xul));
        xul_delete(g_xul);
}

static void
test_xtime(void)
{
}

GTestCase *
xul_test_xtime_case(void)
{
        return g_test_create_case("xtime", 0, NULL, test_xtime_setup, test_xtime, test_xtime_teardown);
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
