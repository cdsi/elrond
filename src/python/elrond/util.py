import time

from threading import Lock

def Property(f):

    return property(**f())

class Object(object):

    pass

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

class Lockable(object):

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
        if self.__lock not in self.__locks: self.__locks[self.__lock] = Lock()
