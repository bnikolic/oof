# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Testing script for 3D Kolmogorov turbulence
#

import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import pybnlib
import numarray
from  matplotlib import pylab




def GenK(N):
    grid=pybnlib.doubleArray( N*N*N)
    rfn=pybnlib.NormDistZM(1.0)
    pybnlib.Kolmogorov3D( grid, N, rfn)
    res=numarray.zeros( (N,N,N), numarray.Float64)
    for k in range(N):
        for j in range(N):
            for i in range(N):
                res[i,j,k] = grid[ k*N*N+j*N+i]
    return res
