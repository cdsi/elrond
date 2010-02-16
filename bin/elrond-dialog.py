#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Dialog, Window

def callback():
        while True:
                try:
                        with open(socket, 'r') as fd:
                                # TODO: readline needs a timeout
                                yield fd.readline()
                except:
                        pass

op = OptionParser('%prog [options]')

op.add_option('--socket', action='store', dest='socket',
              help='The named pipe created by mkfifo')
op.add_option('--labels', action='store', dest='labels',
              help='label1:label2:label3 etc...')

op.add_option('--title', action='store', dest='title', default=None,
              help='The dialog window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the dialog window is not closable.')

(options, args) = op.parse_args()

if options.socket == None:
        op.error('--socket=... is required')
if options.labels == None:
        op.error('--labels=... is required')

socket = options.socket

dialog = Dialog()
dialog.labels = options.labels

window = Window(widget=dialog)
window.title = options.title
window.deletable = options.deletable

dialog.play(callback)

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
