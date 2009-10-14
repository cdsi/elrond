#!/usr/bin/env python

import os

from elrond.ui import SaveAs

def selection_cb(selection):
        print 'selection =', selection

if __name__ == '__main__':

        chooser = SaveAs()

        chooser.callback = selection_cb
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
