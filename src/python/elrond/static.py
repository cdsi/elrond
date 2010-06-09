from __future__ import division
from __future__ import with_statement

HEXFILT = ''.join([(len(repr(chr(x))) == 3) and chr(x) or '.' for x in range(256)])

def hexdump(src, size, columns=32):
        """ http://code.activestate.com/recipes/142812/ """

        result = []

        for i in xrange(0, size, columns):
                sub1 = src[i:i + columns]
                hexa = ' '.join(['%02X' % ord(x) for x in sub1])
                sub2 = sub1.translate(HEXFILT)
                result.append('%04X   %-*s   %s\n' % (i, columns * 3, hexa, sub2))

        return ''.join(result)

def is_odd(x):
        return bool(x & 0x01)

def number_of_1_bits(x):
        count = 0
        while (x):
                count = count + (x & 0x01)
                x = x >> 1
        return count

def set_odd_parity(bits, paritybit=0x8000):
        if not is_odd(number_of_1_bits(bits)):
                bits = bits | paritybit
        return bits

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
