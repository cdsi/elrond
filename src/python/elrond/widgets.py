from __future__ import division
from __future__ import with_statement

import gobject
import gtk

from elrond.ui import Console, Dialog, Plane, Window

class Alignment(gtk.Alignment):

        def do_size_request(self, requisition):
                size = self.subwidget.widget.size_request()
                requisition.width, requisition.height = size

        def do_size_allocate(self, allocation):
                self.subwidget.widget.size_allocate(allocation)

class ConsoleWidget(Alignment):
        __gtype_name__ = 'ConsoleWidget'

        def __init__(self):
                Alignment.__init__(self)

                self.subwidget = Console()
                self.add(self.subwidget.widget)

gobject.type_register(ConsoleWidget)

class DialogWidget(Alignment):
        __gtype_name__ = 'DialogWidget'

        def __init__(self):
                Alignment.__init__(self)

                self.subwidget = Dialog()
                self.add(self.subwidget.widget)

gobject.type_register(DialogWidget)

class PlaneWidget(Alignment):
        __gtype_name__ = 'PlaneWidget'

        def __init__(self):
                Alignment.__init__(self)

                self.subwidget = Plane()
                self.add(self.subwidget.widget)

gobject.type_register(PlaneWidget)

class WindowWidget(gtk.Window):
        __gtype_name__ = 'WindowWidget'

        def __init__(self):
                gtk.Window.__init__(self)

                self.subwidget = Window()
                self.add(self.subwidget.widget)

gobject.type_register(WindowWidget)

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
