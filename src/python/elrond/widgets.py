from __future__ import division
from __future__ import with_statement

import gobject
import gtk

from elrond.ui import Example, Console, Dialog, Plane, Window, YesNo

class Alignment(gtk.Alignment):

        def do_size_request(self, requisition):
                size = self.subwidget.widget.size_request()
                requisition.width, requisition.height = size

        def do_size_allocate(self, allocation):
                self.subwidget.widget.size_allocate(allocation)

class ElrondExampleWidget(Alignment):
        __gtype_name__ = 'ElrondExampleWidget'

        def __init__(self):
                Alignment.__init__(self)

                self.subwidget = Example()
                self.add(self.subwidget.widget)

gobject.type_register(ElrondExampleWidget)

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

class YesNoWidget(Alignment):
        __gtype_name__ = 'YesNoWidget'

        def __init__(self):
                Alignment.__init__(self)

                self.subwidget = YesNo()
                self.add(self.subwidget.widget)

gobject.type_register(YesNoWidget)

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
