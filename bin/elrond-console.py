#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Console, Window

op = OptionParser('%prog [options]')

op.add_option('--socket', action='store', dest='socket', default=None,
              help='The named pipe created by mkfifo')

op.add_option('--title', action='store', dest='title', default=None,
              help='The console window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the console window is not closable.')

(options, args) = op.parse_args()

if options.socket == None:
        op.error('--socket=... is required')

console = Console()
console.socket = options.socket

window = Window(widget=console)
window.title = options.title
window.deletable = options.deletable

window.show()
window.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
