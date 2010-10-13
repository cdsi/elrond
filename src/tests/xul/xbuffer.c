#include "elrond_common.h"

#include "xul.h"

#include "xultest.h"

xul_t *g_xul;

xul_buffer_t *g_buffer;
guint8 *g_scratch;

#define SCRATCH_SIZE 1024

static void
test_xbuffer_setup(void)
{
        g_xul = xul_new();
        g_assert(XUL_IS_VALID(g_xul));
        g_buffer = xul_buffer_new(g_xul);

        g_scratch = (guint8 *) g_malloc0(SCRATCH_SIZE);
        g_scratch[SCRATCH_SIZE - 42] = 0x42;

        xul_buffer_append(g_xul, g_buffer, g_scratch, SCRATCH_SIZE);
}

static void
test_xbuffer_teardown(void)
{
        g_assert(XUL_IS_VALID(g_xul));
        xul_buffer_delete(g_xul, g_buffer);
        xul_delete(g_xul);

        g_free((gpointer) g_scratch);
}

static void
test_xbuffer(void)
{
        g_assert(XUL_IS_VALID(g_xul));

        guint8 *buffer = xul_buffer_get_buffer(g_xul, g_buffer);

        g_assert_cmphex(buffer[SCRATCH_SIZE - 42], ==, 0x42);
}

GTestCase *
xul_test_xbuffer_case(void)
{
        return TESTCASE("xul-buffer", test_xbuffer_setup, test_xbuffer, test_xbuffer_teardown);
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
