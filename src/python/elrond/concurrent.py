from __future__ import division
from __future__ import with_statement

class Task(Object):
        """http://unpythonic.blogspot.com/2007/08/using-threads-in-pygtk.html
        """

        def __loop(self, rc):
                if rc is None:
                        rc = ()
                if not isinstance(rc, tuple):
                        rc = (rc,)
                self.callback(*rc)

        def __start(self, *args, **kwargs):
                for rc in self.generator(*args, **kwargs):
                        if self.callback is not None:
                                gobject.idle_add(self.__loop, rc)
                if self.complete is not None:
                        gobject.idle_add(self.complete)

        def start(self, *args, **kwargs):
                if self.__running:
                        return

                self.__running = True
                thread = threading.Thread(target=self.__start, args=args, kwargs=kwargs)
                thread.start()

        def stop(self):
                if not self.__running:
                        return

                self.__running = False

        def kill(self):
                self.stop()
                thread.exit()

        def __init__(self, generator, callback=None, complete=None):
                self.generator = generator
                self.callback = callback
                self.complete = complete

                self.__running = False

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
