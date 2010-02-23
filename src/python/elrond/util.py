from __future__ import division
from __future__ import with_statement

import time

from ConfigParser import SafeConfigParser
from threading import Lock

from decorator import decorator

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

#
# see: http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/426406
#

class Section(Object):

        def __getattr__(self, name):
                value = self.__parser.get(self.__name, name)
                if isinstance(value, str):
                        xvalue = value
                        if value.upper() ==  "TRUE": xvalue = True
                        if value.upper() == "FALSE": xvalue = False
                        value = xvalue
                return value

        def __init__(self, name, parser):
                self.__name = name
                self.__parser = parser

class Prefs(Object):

        def __getattr__(self, name):
                if name in self.__parser.sections():
                        return Section(name, self.__parser)
                else:
                        return None

        def __str__(self):
                p = self.__parser
                result = []
                result.append('<prefs %s>' % self.__prefsname)
                for s in p.sections():
                        result.append('[%s]' % s)
                        for o in p.options(s):
                                result.append('%s=%s' % (o, p.get(s, o)))
                return '\n'.join(result)

        def get(self, section, option):
                self.__parser.set(section, option)

        def set(self, section, option, value):
                self.__parser.set(section, option, str(value))

        def open(self, prefspath, prefsname):
                self.__prefsname = prefspath + '/' + prefsname
                self.__parser.read(self.__prefsname)

        def write(self):
                fp = open(self.__prefsname, 'w')
                self.__parser.write(fp)
                fp.close()

        def __init__(self):
                self.__parser = SafeConfigParser()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
