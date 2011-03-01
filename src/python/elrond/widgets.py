from __future__ import division
from __future__ import with_statement

import gobject
import gtk

from elrond.ui import Console, Dialog, Plane, Window

class ConsoleWidget(gtk.Alignment):
        __gtype_name__ = 'ConsoleWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.console = Console()
                self.add(self.console.widget)

gobject.type_register(ConsoleWidget)

class DialogWidget(gtk.Alignment):
        __gtype_name__ = 'DialogWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.dialog = Dialog()
                self.add(self.dialog.widget)

gobject.type_register(DialogWidget)

class PlaneWidget(gtk.Alignment):
        __gtype_name__ = 'PlaneWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.plane = Plane()
                self.add(self.plane.widget)

gobject.type_register(PlaneWidget)

class WindowWidget(gtk.Window):
        __gtype_name__ = 'WindowWidget'

        def __init__(self):
                gtk.Window.__init__(self)

                # TODO: "window" is used by gtk.Window
                self.embedded = Window()
                self.add(self.embedded.widget)

gobject.type_register(WindowWidget)

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
