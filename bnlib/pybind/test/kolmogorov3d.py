# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Testing script for 3D Kolmogorov turbulence
#

import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

from setup import *

import pybnlib
import numarray
import numpy
from  matplotlib import pylab




def GenK(N,usenumpy=False):
    grid=pybnlib.doubleArray( N*N*N)
    rfn=pybnlib.NormDistZM(1.0)
    pybnlib.Kolmogorov3D( grid, N, rfn)
    if usenumpy:
        res=numpy.zeros( (N,N,N), numpy.float64)
    else:
        res=numarray.zeros( (N,N,N), numarray.Float64)
        
    for k in range(N):
        for j in range(N):
            for i in range(N):
                res[i,j,k] = grid[ k*N*N+j*N+i]
    return res

def Animate(g):
    for i in range(1,64,5):
        pylab.clf()
        x= g[0:i,:,:]
        y= numarray.sum(x, axis=0)
        pylab.matshow( y)
        pylab.savefig("temp/3dturb-%03i.png" % i)
        
