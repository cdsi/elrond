import os

from optparse import OptionParser

from elrond.ui import Window, YesNo
from elrond.util import Object

class Callback(Object):

        def f(self, answer):
                print 'answer =', answer
                window.exit()

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

callback = Callback()

yesno = YesNo()
yesno.callback = callback.f

window = Window(widget=yesno)
window.title = options.title
window.deletable = options.deletable

yesno.get_answer(options.question)

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
