# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# Initial version 2005.
#
# This file is part of the OOF package and is licensed under GPL v2
"""
Example of how to deconvolve for a Gaussian beam 
"""

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
    fm=pyplot.GaussConvMap(o, o)
    bnmin1utils.SetIC(fm, 
                      params)
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
           fit=["amp", "sigma", "x0", "y0"]):
    """
    Fit the observations
    """
    pm=mkPlanet(o.nx, 
                pradius, 
                mapsize)
    fm=pyplot.GaussConvMap(o,
                           pm)
    
    bnmin1utils.SetIC(fm,
                      ic)
    lmm=pybnmin1.LMMin(fm)
    for p in ["x0", "y0"]:
        lmm.getbyname(p).dofit=1
    lmm.solve()
    chisq=lmm.ChiSquared()
    return [lmm.getbyname(p).getp() for p in  fit] + [chisq]

    


