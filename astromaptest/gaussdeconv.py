# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# Initial version 2005.
#
# This file is part of the OOF package and is licensed under GPL v2
"""
Example of how to deconvolve for a Gaussian beam 
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
    Create mock observation

    :param parms: Parameters for the Gaussian
    """
    o=mkPlanet(npix, 
               pradius, 
               mapsize)
    scratch=pyplot.Map(npix, 
                       npix) 
    fm=pyplot.GaussConvMap(scratch, 
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
           fit=["amp", "x0", "y0", "sigma", "diff", "rho" ]):
    """
    Fit the observations
    """
    npix=o.nx
    pm=mkPlanet(npix, 
                pradius, 
                mapsize)
    fm=pyplot.GaussConvMap(o,
                           pm)
    mo=pyplot.Map(npix, 
                  npix)    
    bnmin1utils.SetIC(fm,
                      ic)
    fm.eval(mo)

    lmm=pybnmin1.LMMin(fm)
    for p in fit:
        lmm.getbyname(p).dofit=1
    m1=pybnmin1.ChiSqMonitor()
    m1.thisown=0
    lmm.AddMon(m1)
    lmm.solve()
    chisq=lmm.ChiSquared()
    m=pyplot.Map(npix, 
                 npix)    
    pyplot.MkRectCS(m, 
                    mapsize*0.5,
                    mapsize*0.5)
    fm.eval(m)
    return pm, mo, m, [lmm.getbyname(p).getp() for p in  fit] + [chisq]

    
def npToMap(a,
            mapsize):
    m=pyplot.Map(*a.shape)
    for i in range(a.shape[0]):
        for j in range(a.shape[1]):
            m.set(i, j, a[i,j])
    pyplot.MkRectCS(m, 
                    mapsize*0.5,
                    mapsize*0.5)
    return m

