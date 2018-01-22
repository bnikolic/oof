"""
Aperture plane amplitude models
"""

import numpy

def gauss(x0, y0, amp, sigma, rho, diff, a):
    """ 
    2D gaussian 
    """
    dx=a[...,0]-x0
    dy= a[...,1]-y0
    r=numpy.hypot(dx, dy)
    return amp*numpy.exp(-1.0/ (2*sigma**2) * (r**2 +
                                               rho*(dx*dy)+
                                               diff*(dx**2-dy**2)))

def dish(R, S, a):
    """
    A dish mask
    """
    r=numpy.hypot(a[...,0], a[...,1])
    res=(r<=R)
    if S>0:
        res*=(r>S)
    return res

