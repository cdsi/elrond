#include "elrond_common.h"

#include "xul.h"

xul_t *g_xul;

static void
test_xshm_setup(void)
{
        g_xul = xul_new();
        xul_init(g_xul);

        xul_rc_e rc;

        rc = xul_shm_map(g_xul, "xultest-shm", 1024);
        if (rc) {
                if (XUL_HAS_ERROR(g_xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(g_xul));
                        xul_error_clear(g_xul);
                }
                g_assert_not_reached();
        }
}

static void
test_xshm_teardown(void)
{
        xul_delete(g_xul);
}

static void
test_xshm(void)
{
        for (guint32 i = 0; i < 1024; i++) {
                xul_shm_poke(g_xul, i, 0x8C);
                g_assert_cmphex(xul_shm_peek(g_xul, i), ==, 0x8C);
        }
}

GTestCase *
xul_test_xshm_case(void)
{
        return g_test_create_case("xshm", 0, NULL, test_xshm_setup, test_xshm, test_xshm_teardown);
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
