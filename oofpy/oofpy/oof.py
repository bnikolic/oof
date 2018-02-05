import inspect
import re

import numpy

from . import zernike, amp

def tosky(a,p):
    """FFT to sky"""
    return numpy.fft.fftshift(numpy.fft.ifft2(numpy.fft.ifftshift(a * numpy.exp(1j*p)))).real

def toskyDz(a, p, dz):
    """Predict beam maps including a defocus
    
    :param dz: 3d array with outermost dimension representing the
    different defocus settings
    """
    res=[]
    for i in range(dz.shape[0]):
        res.append(tosky(a, p+dz[i]))
    return numpy.array(res)

def mkPredFn(nzern, g, dzl,
             initv,
             omitp=[],
             dish=None):
    """Make a predictor function which takes a perameter array and returns the beam maps
    
    :param nzern: Maximum order of Zernike to use

    :param g: Grid on which to evaluate
    
    :param dzl: Array of defocus phase screen of shape [number of defocus]+g.shape

    :param initv: An initial vector containing values for all
    parameters. Parameters which are omited will always have this value.

    :param omitp: Parameters to omit

    """
    # Make our own copy
    initv=numpy.array(initv)
    zlc=zernike.mkCFn(nzern, g)
    nzpoly=zernike.N(nzern)
    # This is the list of all parameter names
    parl=zlc.parnames+inspect.getargspec(amp.gauss).args[:-1]
    # Indices of params we will fit for
    fiti=numpy.array([i for i,xz in enumerate(parl) if  xz not in omitp])
    if dish is None:
        dish=amp.dish(1, 0, g)
    def f(pars):
        initv[fiti]=pars
        p=zlc(initv[0:nzpoly])
        a=amp.gauss(* (list(initv[nzpoly:]) +[g])) * dish
        return toskyDz(a, p, dzl)
    return f, numpy.array(parl)[fiti]
