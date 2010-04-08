from __future__ import division
from __future__ import with_statement

import thread
import threading

import gobject

from elrond.util import APIDepricated, Object

class Task(Object):
        """http://unpythonic.blogspot.com/2007/08/using-threads-in-pygtk.html
        """

        def __loop(self, rc):
                if not self.__callback:
                        return
                if not rc:
                        rc = ()
                if not isinstance(rc, tuple):
                        rc = (rc,)
                self.__callback(*rc)

        def __start(self, *args, **kwargs):
                for rc in self.__producer(*args, **kwargs):
                        if not self.running:
                                break
                        gobject.idle_add(self.__loop, rc)
                if self.__complete:
                        gobject.idle_add(self.__complete)

        def start(self, *args, **kwargs):
                if self.running:
                        return

                self.running = True

                thread = threading.Thread(target=self.__start, args=args, kwargs=kwargs)
                thread.start()

        def stop(self):
                self.running = False

        def kill(self):
                self.running = False
                try:
                        thread.exit()
                except SystemExit:
                        pass

        def __init__(self, producer, callback=None, complete=None):
                self.__producer = producer
                self.__callback = callback
                self.__complete = complete

                self.running = False

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
