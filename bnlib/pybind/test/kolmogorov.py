# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# May 2007
#
# Testing script for Kolmogorov phase screen generation
#
# Setting python path if necessary:
# import sys; sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])
# or
# import sys ; sys.path.extend(["/home/bnikolic/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import sys

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

def CopyToNA(grid,
             N):

    res=numarray.zeros( (N,N),
                        numarray.Float64)
    for j in range(N):
        for i in range(N):
            res[i,j]=grid[j*N+i]

    return res
    
def GenKolmogorov(N,
                  seed=0):

    grid=pybnlib.doubleArray( N*N)

    pybnlib.KolmogorovPlatform(N,
                               grid,
                               seed)
    return CopyToNA(grid,N)

def GenKolmogorovV2(N,
                    seed=None,
                    sfn=pybnlib.KolPowerLawFn(pybnlib.KolPowerLawFn.D3Thick)):

    grid=pybnlib.doubleArray( N*N)

    rfn=pybnlib.NormDistZM(1.0)
    if seed != None:
        rfn.reseed(seed)
    else:
        rfn.reseed(pybnlib.TimeSeed())

    pybnlib.KolmogorovPlatform(N,
                               grid,
                               sfn,
                               rfn)

    return CopyToNA(grid,N)
    
    


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
    

def PlotPowerLaws():

    """
    Test the kolmogorov power law generation functions
    """
    
    def PlotFn(f):
        xa=numarray.arange(1.0, 100.0, 1.0)
        ya=numarray.array([ f(x) for x in xa] )
        pylab.loglog( xa, ya)

    
    PlotFn(pybnlib.KolPowerLawFn(pybnlib.KolPowerLawFn.D3Thin))
    PlotFn(pybnlib.KolPowerLawFn(pybnlib.KolPowerLawFn.D3Thick))
    PlotFn(pybnlib.Kol3DBreakLaw(10.0) )
    

# Plot as
# pylab.plot( [x[1] for x in ss] ) ; pylab.plot( [ 6.88 * ( x[0]/ 2050.0 )**(5.0/3) for x in ss] ) ; pylab.show()
        
        
def TestKolmogorovCorners():

    rfn=pybnlib.NormDistZM(1.0)
    sfn=pybnlib.KolPowerLawFn(pybnlib.KolPowerLawFn.D3Thin)
    print pybnlib.KolmogorovCorners(sfn, rfn)
    

def BreakIllustration(seed=11):

    for x in [1 , 2 , 4, 8, 16 , 25, 100]:
        pylab.clf()
        m4=GenKolmogorovV2(1025, seed,  pybnlib.Kol3DBreakLaw(1.0/x) )
        pylab.matshow(m4)
        pylab.savefig("temp/breakill-%03i.png" % x)
        
        
        
    

    







