from __future__ import division
from __future__ import with_statement

def reverse_bits(value, nbits=32):
        """ Reverse the bits in an int. Assume 32-bits by default. """

        value = list(str(bin(value)))

        value.reverse()
        value = value[:value.index('b')]
        value = value + ['0'] * (nbits - len(value))
        value = int(''.join(value), 2)

        return value

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
