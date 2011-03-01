import os

from optparse import OptionParser

import elrond.widgets

from elrond.ui import YesNoApp
from elrond.util import Object

def callback(answer):
        print 'answer =', answer
        app.exit()

op = OptionParser('%prog [options]')

op.add_option('--question', action='store', dest='question',
              help='A question that can be answered with Yes/No.')

op.add_option('--title', action='store', dest='title', default=None,
              help='The window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the window is not closable.')

(options, args) = op.parse_args()

if not options.question:
        op.error('--question=... is required')

app = YesNoApp()
app.title = options.title
app.deletable = options.deletable

yesno = app.get_subwidget('elrond-yesno-widget')
yesno.callback = callback

yesno.get_answer(options.question)

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
