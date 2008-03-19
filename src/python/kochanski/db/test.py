import random
import os
import unittest

from kochanski.db import DB, Persistable, Int, Str
from kochanski.util import Benchmark

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

class testcase(unittest.TestCase):

	def setUp(self):
		pass

	def tearDown(self):
		pass

	def testDB(self):
		print

		Benchmark.enabled = True
		Benchmark.categories = set(['SET', 'GET'])

		self.db = DB()
		self.db.path = os.environ['KOCHANSKI_DB']
		self.db.name = 'kochanski.db'
		self.db.open()

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

		self.db.close()
