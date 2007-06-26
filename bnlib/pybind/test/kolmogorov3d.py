# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# June 2007
#
# Testing script for 3D Kolmogorov turbulence
#

import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

from setup import *

import pyplot
import pybnlib
import numarray
import numpy
from  matplotlib import pylab


def GenKMap( npix):

    "Generate a map with Kolmogorov Turbulunce"

    if ( not (npix & 1 ) ):
        raise "number of pixels must be odd (and 2^n+1 )"
    
    m1=pyplot.Map(npix, npix)
    pyplot.KolmogorovMap(m1,0.000001)

    return m1


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

def GenKV2(Nx,Ny,Nz):

    """
    Plot projections as
    pylab.matshow(numarray.sum( g, axis=0))  
    """
    grid=pybnlib.doubleArray( Nx*Ny*Nz)
    rfn=pybnlib.NormDistZM(1.0)
    pybnlib.Kolmogorov3D( grid, Nx,Ny,Nz, rfn)
    res=numarray.zeros( (Nx,Ny,Nz), numarray.Float64)
        
    for k in range(Nz):
        for j in range(Ny):
            for i in range(Nx):
                res[i,j,k] = grid[ k*Nx*Ny+j*Nx+i]
    return res

def Animate(g):
    for i in range(1,64,5):
        pylab.clf()
        x= g[0:i,:,:]
        y= numarray.sum(x, axis=0)
        pylab.matshow( y)
        pylab.savefig("temp/3dturb-%03i.png" % i)


def MapFromA(a):
    m=pyplot.Map(a.shape[0], a.shape[1])
    for i in range( a.shape[0]):
        for j in range( a.shape[1] ):
            m.set(i,j, a[i,j])
    return m

def SfnFromM(m):

    "Converts an array to AstroMap::Map and calculates structure fn"

    sfn=pyplot.DoubleVector()
    count=pyplot.SizeTVector()
    pyplot.RndStructureFn( m, 10 ,
                           sfn, count)

    return ( numarray.array(sfn[1:]),
             numarray.array(count[1:]))
    
