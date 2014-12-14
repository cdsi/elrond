# -*- coding: utf-8 -*-

import dl
import sys

dlopenflags = sys.getdlopenflags()
sys.setdlopenflags(dl.RTLD_LAZY | dl.RTLD_GLOBAL)
from elrond.backends.xul import *
sys.setdlopenflags(dlopenflags)
