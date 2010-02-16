#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Console, Window

def callback():
        while True:
                try:
                        with open(socket, 'r') as fd:
                                # TODO: readline needs a timeout
                                yield fd.readline()
                except:
                        pass

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

socket = options.socket

console = Console()

window = Window(widget=console)
window.title = options.title
window.deletable = options.deletable

console.play(callback)

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
