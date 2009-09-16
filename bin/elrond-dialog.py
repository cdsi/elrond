#!/usr/bin/env python

from optparse import OptionParser

from elrond.ui import Dialog

if __name__ == '__main__':
        op = OptionParser('%prog [options]')

        op.add_option('--socket', action='store', dest='socket',
                      help='The named pipe created by mkfifo')
        op.add_option('--labels', action='store', dest='labels',
                      help='label1:label2:label3 etc...')

        (options, args) = op.parse_args()

        if options.socket == None:
                op.error('--socket=... is required')
        if options.labels == None:
                op.error('--labels=... is required')

        dialog = Dialog()

        dialog.socket = options.socket
        dialog.labels = options.labels

        dialog.play()

        dialog.show()
        dialog.run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
