import unittest

from elrond.db import test as dbtest
from elrond.util import test as utiltest

def testsuite():
	__testsuite = unittest.TestSuite()
	__testsuite.addTest(unittest.TestLoader().loadTestsFromModule(dbtest))
	__testsuite.addTest(unittest.TestLoader().loadTestsFromModule(utiltest))
	return __testsuite
