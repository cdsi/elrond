#!/usr/bin/env python

import os
import sys

from django.core.handlers.wsgi import WSGIHandler
from flup.server.fcgi import WSGIServer

os.environ['DJANGO_SETTINGS_MODULE'] = 'elrond.www.settings'
sys.path.append(os.environ['ELROND_SRC'])

WSGIServer(WSGIHandler()).run()

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
