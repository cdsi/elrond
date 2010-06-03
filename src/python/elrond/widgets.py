import gobject
import gtk

from elrond.ui import Console, Dialog, Plane, Window

class ConsoleWidget(gtk.Alignment):
        __gtype_name__ = 'ConsoleWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.console = Console()
                self.add(self.console.widget)

class DialogWidget(gtk.Alignment):
        __gtype_name__ = 'DialogWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.dialog = Dialog()
                self.add(self.dialog.widget)

class PlaneWidget(gtk.Alignment):
        __gtype_name__ = 'PlaneWidget'

        def __init__(self):
                gtk.Alignment.__init__(self)

                self.plane = Plane()
                self.add(self.plane.widget)

class WindowWidget(gtk.Alignment):
        __gtype_name__ = 'WindowWidget'

        # TODO: top-level widgets need some tlc...

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
