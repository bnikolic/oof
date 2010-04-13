# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# Initial version 2005.
#
# This file is part of the OOF package and is licensed under GPL v2
"""
Example of how to deconvolve for a Gaussian beam, assuming underlying
source is a planet represetned by a tapered disk
"""

import pickle
import numpy

import localsetup

import pybnlib
import pyplot
import pybnmin1
import bnmin1utils


def setPlanet(m,
              radius,
              Cm=0):
    """
    Set the map to with a planet-like shape
    """
    pfn=pybnlib.TaperedTopHatDD()
    pfn.radius= radius
    pfn.Cm = Cm
    pyplot.WorldSet(m,
                    pfn)

def mkPlanet(npix,
             pradius,
             mapsize,
             Cm=0):
    """
    Create a map with planet model 

    :param npix: Size of map in pixels per dimension

    :param pradius: Radius of planet

    :param mapsize: Angular size to assign to each map dimension

    Example:

    >>> m=mkPlanet(256, 20.0, 500.0)

    """
    m=pyplot.Map(npix, npix)
    pyplot.MkRectCS(m, 
                    mapsize*0.5,
                    mapsize*0.5)
    setPlanet(m,
              pradius,
              Cm=Cm)
    return m


def mkMockObs(npix,
              pradius,
              mapsize,
              noise,
              params=[1, 0,  0,  1.0, 0, 0]):
    """
    Create a mock observation

    :param parms: Parameters for the Gaussian. The order is amplitude,
    x0, y0, sigma, rho and diff
    """
    o=mkPlanet(npix, 
               pradius, 
               mapsize)
    # First parameter is not used since we never fit
    fm=pyplot.GaussConvMap(o, 
                           o)
    bnmin1utils.SetIC(fm, 
                      params)
    o.mult(0)
    fm.eval(o)
    mnoise=pyplot.Map(npix, npix)
    pyplot.NormDist(mnoise, 
                    1.0*noise)
    o.add(mnoise)
    return o


def fitObs(o,
           pradius,
           mapsize,
           ic=[1, 0,  0,  1.0, 0, 0],
           fit=["amp", "x0", "y0", "sigma", "diff", "rho" ],
           Cm=0):
    """
    Fit the observations.

    :param pradius: Radius of the planet

    :param mapsize: Angular size of the map
    
    :param ic: Initial condition from which to start the minimiser
    
    :param fit: List of parameters to fit for -- default is all
    parameters

    :returns: List of [best fitting model (*after convolution*), 
    best fitting Gaussian parameters, final chi-sq]

    Example:
    >>> mm=npToMap(pickle.load(open("tmp_beam.sav")), 50)
    >>> m, r, ch=fitObs(obsmap, 1.0, 50.0, ic=[0, 0, 0, 1.0, 0, 0])

    """
    npix=o.nx
    pm=mkPlanet(npix, 
                pradius, 
                mapsize,
                Cm=Cm)
    fm=pyplot.GaussConvMap(o,
                           pm)
    lmm=pybnmin1.LMMin(fm)
    for p in fit:
        lmm.getbyname(p).dofit=1
    m1=pybnmin1.ChiSqMonitor()
    m1.thisown=0
    lmm.AddMon(m1)
    lmm.solve()
    chisq=lmm.ChiSquared()
    bestmodel=pyplot.Map(npix, 
                         npix)    
    pyplot.MkRectCS(bestmodel, 
                    mapsize*0.5,
                    mapsize*0.5)
    fm.eval(bestmodel)
    return bestmodel, [lmm.getbyname(p).getp() for p in  fit], chisq

    
def npToMap(a,
            mapsize):
    """
    Conver a numpy array to a map. 
    
    :param mapsize: Angluar size of one of the dimensions of the map. 

    """
    m=pyplot.Map(*a.shape)
    for i in range(a.shape[0]):
        for j in range(a.shape[1]):
            m.set(i, j, a[i,j])
    pyplot.MkRectCS(m, 
                    mapsize*0.5,
                    mapsize*0.5)
    return m

