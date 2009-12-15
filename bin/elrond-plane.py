#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Plane

op = OptionParser('%prog [options]')

op.add_option('--socket', action='store', dest='socket',
              help='The named pipe created by mkfifo')

op.add_option('--title', action='store', dest='title', default=None,
              help='The plane window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the plane window is not closable.')

(options, args) = op.parse_args()

if options.socket == None:
        op.error('--socket=... is required')

plane = Plane()

plane.socket = socket

plane.title = options.title
dialog.deletable = options.deletable

plane.show()
plane.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
