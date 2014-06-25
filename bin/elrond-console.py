from functools import partial
from optparse import OptionParser

import elrond.widgets

from elrond.ui import ConsoleApp

def callback(socket):
        # This will block indefinitely until something is written to the pipe.
        # As soon as something is written to the pipe, and this writer closes (or exits)
        # (e.g. echo "foo:bar" > /path/to/socket) then the open call will terminate.
        # This is why we loop indefinitely. If the socket is opened by a long-lived
        # application, then this is not an issue. And since there is no timeout on this
        # "read", there is no way to cleanly terminate this application.
        while True:
                try:
                        for line in open(socket, 'r'):
                                yield line
                except FileNotFoundError as e:
                        pass

op = OptionParser('%prog [options]')

op.add_option('--socket', action='store', dest='socket',
              help='The named pipe created by mkfifo')

op.add_option('--title', action='store', dest='title', default=None,
              help='The window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the window is not closable.')

(options, args) = op.parse_args()

if not options.socket:
        op.error('--socket=... is required')

app = ConsoleApp()
app.title = options.title
app.deletable = options.deletable

console = app.get_subwidget('elrond-console-widget')
console.play(partial(callback, options.socket))

app.show()
app.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
