from __future__ import division
from __future__ import with_statement

def clamp(x, l=None, u=None):
        """return value limited by lower and/or upper bounds"""

        if u is not None:
                x = min(x, u)
        if l is not None:
                x = max(x, l)

        return x

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
