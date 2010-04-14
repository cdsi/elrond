from __future__ import division
from __future__ import with_statement

import unittest

import random
import os
import time

from elrond.db import DB, Persistable, Int, Str
from elrond.util import APIDepricated, APIDepricatedError, APINotImplemented, APINotImplementedError
from elrond.util import Benchmark, Object, Preferences, Property

from elrond.static import *

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
                """The power measurement in dB."""

                def fget(self):
                        return self.__dB

                def fset(self, dB):
                        self.__dB = dB

                return locals()

class StaticTestCase(unittest.TestCase):

        def testAll(self):

                self.assertEquals(reverse_bits(0x01, nbits=4), 0x08)
                self.assertEquals(reverse_bits(0x08, nbits=4), 0x01)

                self.assertEquals(reverse_bits(0x10, nbits=8), 0x08)
                self.assertEquals(reverse_bits(0x80, nbits=8), 0x01)

                self.assertEquals(reverse_bits(0x0101, nbits=16), 0x8080)
                self.assertEquals(reverse_bits(0x0808, nbits=16), 0x1010)

                self.assertEquals(reverse_bits(0x01010101), 0x80808080)
                self.assertEquals(reverse_bits(0x08080808), 0x10101010)

                self.assertEquals(reverse_bits(0x0101010101010101, nbits=64), 0x8080808080808080)
                self.assertEquals(reverse_bits(0x0808080808080808, nbits=64), 0x1010101010101010)

class UtilTestCase(unittest.TestCase):

        def setUp(self):
                pass

        def tearDown(self):
                pass

        def testExceptions(self):
                print

                @APIDepricated
                def __APIDepricated():
                        pass

                @APINotImplemented
                def __APINotImplemented():
                        pass

                self.assertRaises(APIDepricatedError, __APIDepricated)
                self.assertRaises(APINotImplementedError, __APINotImplemented)

        def testBenchmark(self):
                print

                Benchmark.enabled = True
                Benchmark.categories = set(['BENCHMARK'])

                @Benchmark(category=['BENCHMARK'])
                def testSleep():
                        time.sleep(0)

                for i in range(0, 5):
                        testSleep()

        def testObject(self):
                print

                o = Object()

                self.assertEquals(True, o.to_bool(True))
                self.assertEquals(False, o.to_bool(False))

                self.assertEquals(True, o.to_bool("True"))
                self.assertEquals(False, o.to_bool("False"))

                self.assertRaises(TypeError, o.to_bool, 42)
                self.assertRaises(TypeError, o.to_bool, "FOOBAR")

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

        def testPreferences(self):
                print

def testsuite():
        __testsuite = unittest.TestSuite()
        __testsuite.addTest(unittest.TestLoader().loadTestsFromTestCase(DBTestCase))
        __testsuite.addTest(unittest.TestLoader().loadTestsFromTestCase(StaticTestCase))
        __testsuite.addTest(unittest.TestLoader().loadTestsFromTestCase(UtilTestCase))
        return __testsuite

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
