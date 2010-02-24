#include "elrond_common.h"

#include "xul.h"

GTestCase *xul_test_xprefs_case();
GTestCase *xul_test_xtime_case();

int
main(int argc, char **argv)
{
        g_test_init(&argc, &argv, NULL);

        GTestSuite *ts = g_test_get_root();

        g_test_suite_add(ts, xul_test_xprefs_case());
        g_test_suite_add(ts, xul_test_xtime_case());

        return g_test_run();
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
