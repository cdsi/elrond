from __future__ import division
from __future__ import with_statement

import math

import numpy as np

def is_odd(x):
        return bool(x & 0x01)

def clamp(x, l=None, u=None):
        """return value limited by lower and/or upper bounds"""

        if u is not None:
                x = min(x, u)
        if l is not None:
                x = max(x, l)

        return x

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

def dB2P(x):
        """decibels to power"""
        return math.pow(10, x / 10)

def P2dB(x):
        """power to decibels"""
        return math.log10(x) * 10

def dB2V(x):
        """decibels to volts"""
        return math.pow(10, x / 20)

def V2dB(x):
        """volts to decibels"""
        return math.log10(x) * 20

def deg2r(x):
        """degrees to radians"""
        return x * math.pi / 180

def r2deg(x):
        """radians to degrees"""
        return x / math.pi * 180

def deg2mr(x):
        """degrees to milliradians"""
        return deg2r(x) * 1000

def mr2deg(x):
        """milliradians to degrees"""
        return r2deg(x / 1000)

def rms(values):
        return np.sqrt(np.mean((values**2)))

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

# $Id:$
#
# Local Variables:
# indent-tabs-mode: nil
# python-continuation-offset: 2
# python-indent: 8
# End:
# vim: ai et si sw=8 ts=8
