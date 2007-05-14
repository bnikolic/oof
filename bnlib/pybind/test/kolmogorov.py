# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# May 2007
#
# Testing script for Kolmogorov phase screen generation

import pybnlib

import numarray
import numarray.random_array
from  matplotlib import pylab

def MarkGIter( grid,
               o,
               cntruct):

    ci=cntruct(grid.shape[0],o)

    while ci.inBounds():
        i,j=ci.getc()
        print i,j
        grid[i,j]=1
        ci.next()
    

def MarkCiter( grid,
               o):

    """
    e.g.:
    a=numarray.zeros( (9,9) ); MarkCiter(a, 2)
    pylab.matshow(a) ; pylab.show()

    """

    MarkGIter( grid, o , pybnlib.CenterIter)

def MarkEiter( grid,
               o):

    MarkGIter( grid, o , pybnlib.EdgeIter)

def GenKolmogorov(N):

    grid=pybnlib.doubleArray( N*N)
    normv = pybnlib.doubleArray( N*N+2)
    anormv=numarray.random_array.normal(0.0, 1.0 , N*N+2)
    for i,x in enumerate(anormv):
        normv[i]=x

    pybnlib.KolmogorovPlatform(N,
                               grid,
                               normv)

    res=numarray.zeros( (N,N),
                        numarray.Float64)
    for j in range(N):
        for i in range(N):
            res[i,j]=grid[j*N+i]

    return res


def Structure(a):

    N=a.shape[0]
    res=[]
    for d in range( 1 , N/2):
        x= a[:,d:] - a[:,:-1*d]
        res.append( ( d, (x**2).mean() ))
    return res

def TwoPointCross(a, sep):

    m=a.shape[0]/2

    return a[:,m - sep/2] - a[:,m + sep/2]

def TwoPointLong(a, sep):

    m=a.shape[0]/2
    ds=sep/2

    return a[ds:,m] - a[:-ds,m]
    

    

# Plot as
# pylab.plot( [x[1] for x in ss] ) ; pylab.plot( [ 6.88 * ( x[0]/ 2050.0 )**(5.0/3) for x in ss] ) ; pylab.show()
        
        
        
    
    
    

    







