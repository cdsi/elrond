import decorator
import time

def Property(f):

    return property(**f())

class Object(object):

    pass

class Benchmark(Object):

    enabled = False
    categories = set([])

    @decorator
    def __call__(self, __f):
        if not self.enabled or not self.__category & self.categories:
            return __f

        def __benchmark(*args, **kwargs):
            __t1 = time.time()
            __rc = __f(*args, **kwargs)
            __t2 = time.time()
            print 'benchmark: call took %f s: %s' % (__t2 - __t1, __f.__name__)
            return __rc

        # __benchmark.__doc__ = __f.__doc__
        return __benchmark

    def __init__(self, category=None):
        self.__category = set(category)
