"""
Zernike polynomials
"""
from math import factorial as fact
import numpy

def ev(n, l, a):
    """Evaluate zernike polynomial (n,l)
    
    :param a: The array over which to evaluate, of form [ [x,y] ]
    
    Example: evalZern(2,0, numpy.moveaxis(numpy.mgrid[-1:1:64j, -1:1:64j], 0, -1) )
    
    """
    m=abs(l)
    nradterms= 1+ (n-m)//2
    radpowers= n - 2*numpy.arange(nradterms)
    radcoeffs= numpy.array(list(map(lambda s: (-1)**s * fact(n-s) / ( fact(s) * fact ( (n+m)/2 -s ) * fact( (n-m)/2 -s )),
                                    numpy.arange(nradterms))))
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

def N(nmax):
    "Number of polynomials up to and including order nmax"
    return nmax*(nmax+3)//2 +1

def mkCFn(nmax, a):
    """Make a function which evaluates linear combinations of Zernike polynomials

    :param nmax: Maximum Zernike order to include

    example: 
    x=mkCFn(2, numpy.moveaxis(numpy.mgrid[-1:1:64j, -1:1:64j], 0, -1) )
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(ev(n, l, a))
    zz=numpy.array(zz)
    def lcfn(c):
        return (c*numpy.moveaxis(zz, 0, -1)).sum(axis=-1)
    lcfn.parnames=["z%i"%i for i in range(zz.shape[0])]
    return lcfn

