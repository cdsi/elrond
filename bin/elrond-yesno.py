import os

from optparse import OptionParser

from elrond.ui import Window, YesNo

def callback(answer):
        print 'answer =', answer

op = OptionParser('%prog [options]')

op.add_option('--question', action='store', dest='question',
              help='The question to ask.')

op.add_option('--title', action='store', dest='title', default=None,
              help='The dialog window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the dialog window is not closable.')

(options, args) = op.parse_args()

if options.question == None:
        op.error('--question=... is required')

yesno = YesNo()

window = Window(widget=yesno)
window.title = options.title
window.deletable = options.deletable

yesno.callback = callback
yesno.get_answer(question=options.question)

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
