import time
import unittest

from elrond.util import Benchmark, Property

class Power(object):

	@Property
        def dB():
                doc = """The power measurement in dB."""

                def fget(self):
                        return self.__dB

                def fset(self, dB):
                        self.__dB = dB

                return locals()

class testcase(unittest.TestCase):

	def setUp(self):
		pass

	def tearDown(self):
		pass

	def testBenchmark(self):
		print

		Benchmark.enabled = True
		Benchmark.categories = set(['BENCHMARK'])

		@Benchmark(category=['BENCHMARK'])
		def testSleep():
			time.sleep(0)

		for i in range(0, 5):
			testSleep()

	def testProperty(self):
		print

		Benchmark.enabled = True
		Benchmark.categories = set(['PROPERTY'])

		self.power = Power()

		@Benchmark(category=['PROPERTY'])
		def testSet(dB):
			self.power.dB = dB

		@Benchmark(category=['PROPERTY'])
		def testGet():
			return self.power.dB

		dB = 100.0

		testSet(dB)
		self.assertAlmostEqual(dB, testGet())
