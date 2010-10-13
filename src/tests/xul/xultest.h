#ifndef XULTEST_H
#define XULTEST_H 1

#if GLIB_CHECK_VERSION(2, 25, 12)
typedef GTestFixtureFunc TESTCASEFUNC;
#else
typedef void (*TESTCASEFUNC) (void);
#endif

#define TESTCASE(name, setup, test, teardown) g_test_create_case(name, 0, NULL, (TESTCASEFUNC) setup, (TESTCASEFUNC) test, (TESTCASEFUNC) teardown)

GTestCase *xul_test_xbuffer_case();
GTestCase *xul_test_xprefs_case();
GTestCase *xul_test_shm_case();
GTestCase *xul_test_xtime_case();

#endif                          /* ! XULTEST_H */

/*
 * $Id:$
 *
 * Local Variables:
 * c-file-style: "linux"
 * indent-tabs-mode: nil
 * End:
 * vim: ai et si sw=8 ts=8
 */
