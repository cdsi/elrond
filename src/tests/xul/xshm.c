#include "elrond_common.h"

#include "xul.h"

xul_t *g_xul;
xul_shm_t *g_shm;

static void
test_shm_setup(void)
{
        g_xul = xul_new();
        xul_init(g_xul);

        g_shm = xul_shm_new(g_xul);
        xul_shm_init(g_shm);

        xul_rc_e rc;

        rc = xul_shm_map(g_shm, "xultest-shm", 1024);
        if (rc) {
                if (XUL_HAS_ERROR(g_xul)) {
                        g_fprintf(stderr, "ERROR: %s\n", xul_error_message_get(g_xul));
                        xul_error_clear(g_xul);
                }
                g_assert_not_reached();
        }
}

static void
test_shm_teardown(void)
{
        xul_shm_delete(g_shm);
        xul_delete(g_xul);
}

static void
test_shm(void)
{
        for (guint32 i = 0; i < 1024; i++) {
                xul_shm_poke(g_shm, i, 0x8C);
                g_assert_cmphex(xul_shm_peek(g_shm, i), ==, 0x8C);
        }
}

GTestCase *
xul_test_shm_case(void)
{
        return g_test_create_case("xul-shm", 0, NULL, test_shm_setup, test_shm, test_shm_teardown);
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
