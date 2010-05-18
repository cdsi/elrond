from __future__ import division
from __future__ import with_statement

HEXFILT = ''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)])

def hexdump(src, size, length=8):
        """ http://code.activestate.com/recipes/142812/ """

        result = []

        for i in xrange(0, size, length):
                sub1 = src[i:i + length]
                hexa = ' '.join(['%02X' % ord(x) for x in sub1])
                sub2 = sub1.translate(HEXFILT)
                result.append('%04X   %-*s   %s\n' % (i, length * 3, hexa, sub2))

        return ''.join(result)

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
