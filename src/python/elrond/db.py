# The Storm ORM. See also: https://storm.canonical.com/
import storm.locals as Storm

from elrond.util import Benchmark, Object

class Float(Storm.Float):

        type = 'F'

class Hex(Storm.Int):

        type = 'H'

        # TODO: convert hex to int

        def __str__(self):
                return hex(self)

class Int(Storm.Int):

        type = 'I'

class Str(Storm.Unicode):

        type = 'S'

class Persistable(Object):

        attrs = {}

        def __getattr__(self, name):
                return Object.__getattr__(self, name)

        def __setattr__(self, name, value):
                if name in self.attrs:
                        self.attrs[name]['value'] = value
                Object.__setattr__(self, name, value)

class DB(Object):

        Benchmark.enabled = True
        Benchmark.categories = set(['DB'])

        @Benchmark(category=['DB'])
        def open(self):
                self.__store = Storm.Store(Storm.create_database('sqlite:' + self.path + '/' + self.name))

        @Benchmark(category=['DB'])
        def close(self):
                pass

        @Benchmark(category=['DB'])
        def create(self, __statement):
                self.__store.execute(__statement)

        @Benchmark(category=['DB'])
        def add(self, __object):
                self.__store.add(__object)

        @Benchmark(category=['DB'])
        def query(self, *__args, **__kwargs):
                return self.__store.find(*__args, **__kwargs)

        @Benchmark(category=['DB'])
        def save(self):
                self.__store.commit()

        @Benchmark(category=['DB'])
        def flush(self):
                self.__store.flush()

        def __init__(self):
                self.path = ''
                self.name = ''

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
