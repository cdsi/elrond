from optparse import OptionParser

import elrond.widgets

from elrond.ui import ExampleApp

op = OptionParser('%prog [options]')

op.add_option('--title', action='store', dest='title', default=None,
              help='The window title.')
op.add_option('--deletable', action='store', dest='deletable', default=True,
              help='When disabled the window is not closable.')

(options, args) = op.parse_args()

app = ExampleApp()
app.title = options.title
app.deletable = options.deletable

console = app.get_subwidget('elrond-example-widget')

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
