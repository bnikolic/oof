# Simulations and tools for shaped reflector telescopes

from math import factorial as fact

import numpy, scipy, pandas
import scipy.optimize

#Plotting setup
from matplotlib import pylab
import matplotlib.pyplot as plt
from matplotlib import cm

def evalZern(n, l, a):
    """Evaluate zernike polynomial (n,l)
    
    :param a: The array over which to evaluate, of form [ [x,y] ]
    
    """
    m=abs(l)
    nradterms= 1+ (n-m)/2
    radpowers= n - 2*numpy.arange(nradterms)
    radcoeffs= numpy.array(map(lambda s: -1**s * fact(n-s) / ( fact(s) * fact ( (n+m)/2 -s ) * fact( (n-m)/2 -s )),
                         numpy.arange(nradterms)))
    r=numpy.hypot(a[...,0], a[...,1])
    phi=numpy.arctan2(a[...,1], a[...,0])
    v=numpy.zeros_like(r)
    for i in range(nradterms):
        v+=radcoeffs[i]*r**radpowers[i]
    if l>0:
        v*=numpy.cos(l*phi);
    elif l<0:
        v*=numpy.sin(-l*phi)
    return v

def nZern(nmax):
    "Number of polynomials up to and including order nmax"
    return nmax*(nmax+3)/2 +1 

def mkZernLCFn(nmax, a):

    """Make a function which evaluates linear combinations of Zernike polynomials

    :param nmax: Maximum Zernike order to include

    example: 
    x=mkZernLCFn(2, numpy.moveaxis(numpy.mgrid[-1:1:64j, -1:1:64j], 0, -1) )
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(evalZern(n, l, a))
    zz=numpy.array(zz)
    def lcfn(c):
        return (c*numpy.moveaxis(zz, 0, -1)).sum(axis=-1)
    return lcfn

def mkZernFitDifFn(nmax, a, v):
    "Make a function that returns difference between model and fit"
    lcfn=mkZernLCFn(nmax, a)
    return lambda x: v-lcfn(x)

def fitZerns(nmax, a, v):
    """
    Example: 
      d=loadZemaxDC("/home/user/QubesIncoming/DocStore/CORRECT3.TXT")
      mm=numpy.logical_and(d.FM==0 , d.FL==0)
      dd=numpy.vstack( [d.AX[mm], d.AY[mm], d.IN[mm] ])
      fitZerns(3, numpy.moveaxis(dd[0:2],0,-1), dd[2] )
    """
    return scipy.optimize.leastsq(mkZernFitDifFn(nmax, a, v),
                                  numpy.zeros(nZern(nmax)),
                                  full_output=True)

    
def loadZemaxDC(fin):
    """Load Zemax direction cosine output file"""
    return pandas.read_table(fin,
                             names=["FL", "FM", "AX", "AY", "IL", "IM", "IN" ] ,
                             delim_whitespace=True)

def plotQuiverN(d, m):
    """Plot the angle arrival direction cosines as a quiver"""
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    surf = ax.quiver(d.AX[mm], d.AY[mm], 0,
                     d.IL[mm], d.IM[mm], d.IN[mm])
    
    ax.set_zlim(-1, 1)    
    plt.show()    

    
