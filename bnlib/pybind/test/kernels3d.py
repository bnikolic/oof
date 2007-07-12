# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# July 2007
#
# Testing of the Kernel generation scripts

from setup import *

from itertools import izip

import numarray

import pybnlib

def KernelPosToArray(kpos):

    nx, ny, nz  = [numarray.zeros( len(kpos) ,
                                   numarray.Int32) for x in range(3) ]
    
    for i,pos in enumerate(kpos):
        nx[i]=pos.i
        ny[i]=pos.j
        nz[i]=pos.k

    return nx, ny, nz

def KernelToNumarray(kpos, kc ):
    
    nx, ny, nz= KernelPosToArray(kpos)

    mx, my, mz  = [ min(y) for y in [nx, ny, nz] ]
    sx , sy, sz  = [ max(y) - min(y) +1 for y in [nx, ny, nz] ]

    res= numarray.zeros( (sx, sy, sz ),
                         numarray.Float64)

    for pos, c in izip(kpos, kc):
        res[ mx + pos.i , my+pos.j , mz+pos.k] = c
    
    return res
