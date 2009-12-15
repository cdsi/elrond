#!/usr/bin/env python

import os

from elrond.ui import SaveAs

def callback(selection):
        print 'selection =', selection

chooser = SaveAs()

chooser.callback = callback
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
