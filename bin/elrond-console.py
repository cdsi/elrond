#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Console

if __name__ == '__main__':
        op = OptionParser('%prog [options]')

        op.add_option('--socket', action='store', dest='socket', default=None,
                      help='The named pipe created by mkfifo')

        op.add_option('--title', action='store', dest='title', default=None,
                      help='The console window title.')
        op.add_option('--embedded', action='store', dest='embedded', default=False,
                      help='When enabled the console window is not closable.')

        (options, args) = op.parse_args()

        if options.socket == None:
                op.error('--socket=... is required')

        console = Console()

        console.socket = options.socket

        console.title = options.title
        console.embedded = options.embedded

        console.show()
        console.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
