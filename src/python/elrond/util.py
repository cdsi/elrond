from __future__ import division
from __future__ import with_statement

import os
import time

from configobj import ConfigObj
from decorator import decorator
from threading import Lock

def is_almost_equal(x1, x2, tolerance=1e-6):
        return math.fabs(x1 - x2) < tolerance

HEXFILT = ''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)])

def hexdump(src, size, length=8):
        """http://code.activestate.com/recipes/142812/"""

        result = []

        for i in xrange(0, size, length):
                sub1 = src[i:i + length]
                hexa = ' '.join(['%02X' % ord(x) for x in sub1])
                sub2 = sub1.translate(HEXFILT)
                result.append('%04X   %-*s   %s\n' % (i, length * 3, hexa, sub2))

        return ''.join(result)

def Property(f):
        return property(**f())

class APIDepricatedError(Exception):
        pass

class APINotImplementedError(Exception):
        pass

@decorator
def APIDepricated(f, *args, **kwargs):
        raise APIDepricatedError('ERROR: "%s" has been depricated and soon will be removed!' % (f))

@decorator
def APINotImplemented(f, *args, **kwargs):
        raise APINotImplementedError('ERROR: "%s" has not been implemented!' % (f))

class Object(object):

        def to_bool(self, value):
                if isinstance(value, bool):
                        return value

                if isinstance(value, str):
                        if value.strip().upper() == 'FALSE':
                                return False
                        if value.strip().upper() == 'TRUE':
                                return True

                raise TypeError

        def readlines(self, filename):
                lines = []

                try:
                        with open(filename, 'r') as fd:
                                lines = [line.strip() for line in fd.readlines()]
                except:
                        pass

                return lines

        def writelines(self, filename, lines):
                with open(filename, 'w') as fd:
                        fd.writelines([line + "\n" for line in lines])

class Benchmark(Object):

        enabled = False
        categories = set([])

        def __call__(self, __f):
                if not self.enabled or not self.__category & self.categories:
                        return __f

                def __benchmark(*args, **kwargs):
                        __t1 = time.time()
                        __rc = __f(*args, **kwargs)
                        __t2 = time.time()
                        print 'benchmark: call took %f s: %s' % (__t2 - __t1, __f.__name__)
                        return __rc

                __benchmark.__doc__ = __f.__doc__
                return __benchmark

        def __init__(self, category=None):
                self.__category = set(category)

__lock = Lock()

def P():
        __lock.acquire()

def V():
        __lock.release()

class Lockable(Object):

        enabled = True
        __locks = {}

        def __call__(self, __f):
                if not self.enabled:
                        return __f

                def __lockable(*args, **kwargs):
                        self.__locks[self.__lock].acquire()
                        __rc = __f(*args, **kwargs)
                        self.__locks[self.__lock].release()
                        return __rc

                __lockable.__doc__ = __f.__doc__
                return __lockable

        def __init__(self, lock='DEFAULT'):
                self.__lock = lock
                if self.__lock not in self.__locks:
                        self.__locks[self.__lock] = Lock()

class Preferences(ConfigObj):

        def __conv(self, section, key):
                value = section[key]

                if isinstance(value, str):
                        if value[:2] == '0x':
                                section[key] = int(value, 16)

        def __init__(self, prefsname):
                ConfigObj.__init__(self, prefsname)

                self.walk(self.__conv, call_on_sections=True)

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
