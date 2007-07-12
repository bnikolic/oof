# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# July 2007
#
# Testing of the Kernel generation scripts

from setup import *

from itertools import izip

import numarray

import pybnlib

import kernel3dutils

dp=pybnlib.Displacement3DV()
dc=pybnlib.doubleV()
pybnlib.GenGaussCylinder(dp,dc, 5, 1, 15, 0,0)
