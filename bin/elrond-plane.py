#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Plane

if __name__ == '__main__':
        op = OptionParser('%prog [options]')

        op.add_option('--socket', action='store', dest='socket',
                      help='The named pipe created by mkfifo')

        (options, args) = op.parse_args()

        if options.socket == None:
                op.error('--socket=... is required')

        plane = Plane()

        plane.socket = socket

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
