from optparse import OptionParser

from elrond.ui import Plane, Window
from elrond.util import Object

class Callback(Object):

        def f(self):
                # This will block indefinitely until something is written to the pipe.
                # As soon as something is written to the pipe, and this writer closes (or exits)
                # (e.g. echo "foo:bar" > /path/to/socket) then the open call will terminate.
                # This is why we loop indefinitely. If the socket is opened by a long-lived
                # application, then this is not an issue. And since there is no timeout on this
                # "read", there is no way to cleanly terminate this application.
                while True:
                        for line in open(self.socket, 'r'):
                                yield line

        def __init__(self, *args, **kwargs):
                Object.__init__(self, *args, **kwargs)

                self.socket = None

op = OptionParser('%prog [options]')

op.add_option('--socket', action='store', dest='socket',
              help='The named pipe created by mkfifo')

op.add_option('--title', action='store', dest='title', default=None,
              help='The window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the window is not closable.')

(options, args) = op.parse_args()

if options.socket == None:
        op.error('--socket=... is required')

callback = Callback()
callback.socket = options.socket

plane = Plane()

window = Window(widget=plane)
window.title = options.title
window.deletable = options.deletable

plane.play(callback.f)

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
