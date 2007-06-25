# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Tests related to investigation of the Grid magnification scheme.

import math

from setup import *

import pybnlib

def SimpleGridMagTest():
    N=3

    a=pybnlib.doubleArray( N*N*N)
    for x,y,z in [ (0,0,0),
                   (N-1,0,0),
                   (0,N-1,0),
                   (0,0,N-1),
                   (N-1,N-1,0),
                   (N-1,0,N-1),
                   (0,N-1,N-1),
                   (N-1,N-1,N-1)]:

        a[x+ y*N + z*N*N]=1

    b=pybnlib.doubleArray( 5*3*3)

    pybnlib.KMagnifyGrid( a, N,
                          b,
                          5,3,3)

    return b
    
