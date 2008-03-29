import unittest

import random
import os
import time

from elrond.db import DB, Persistable, Int, Str
from elrond.util import Benchmark
from elrond.util import Benchmark, Property

class Person(Persistable):
	
	__storm_table__ = 'person'

	id = Int(primary=True)
	name = Str()

	attrs = {
		'name': {
			'lang': 'en',
			'value': name,
		},
	}

	def __init__(self):
		self.id = int(random.random() * 1000)

class DBTestCase(unittest.TestCase):

	Benchmark.enabled = True
	Benchmark.categories = set(['SET', 'GET'])

	def setUp(self):
		print

		self.db = DB()
		self.db.path = os.environ['ELROND_DB']
		self.db.name = 'elrond.db'
		self.db.open()

	def tearDown(self):
		self.db.close()

	def testDB(self):
		name = u'Guido von Rossum'

		@Benchmark(category=['SET'])
		def testSet(name):
			person = Person()
			person.name = name

			self.db.add(person)
			self.db.save()

		@Benchmark(category=['GET'])
		def testGet():
			return self.db.query(Person, Person.name == name)[0].name

		testSet(name)
		self.assertEqual(name, testGet())

class Power(object):

	@Property
        def dB():
                doc = """The power measurement in dB."""

                def fget(self):
                        return self.__dB

                def fset(self, dB):
                        self.__dB = dB

                return locals()

class UtilTestCase(unittest.TestCase):

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

def testsuite():
	__testsuite = unittest.TestSuite()
	__testsuite.addTest(unittest.TestLoader().loadTestsFromTestCase(DBTestCase))
	__testsuite.addTest(unittest.TestLoader().loadTestsFromTestCase(UtilTestCase))
	return __testsuite