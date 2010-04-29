import os

from elrond.ui import SaveAs
from elrond.util import Object

class Callback(Object):

        def f(self, selection):
                print 'selection =', selection

callback = Callback()

chooser = SaveAs()
chooser.callback = callback.f

chooser.get_selection(path=os.environ['ELROND_HOME'], filename='build.sh')

chooser.show()
chooser.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
