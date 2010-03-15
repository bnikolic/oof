# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
"""
Model elevation-dependence of Zernike coefficients according the
elastic deformation (Hooke's law)
"""

import os, string

import numpy
from scipy.optimize import leastsq

def loadData(fnamein):
    res={}
    for l in open(fnamein):
        ld=string.split(l)
        z=int(ld[1])
        el=float(ld[0])
        if z not in res.keys():
            res[z]= []
        res[z].append((el, float(ld[2])))
    return res


def HookeModel(elevs, 
               c, 
               fsin, 
               fcos):
    return c+ fsin*numpy.sin(numpy.radians(elevs)) + fcos*numpy.cos(numpy.radians(elevs))

def HookeModelFit(x0,
                  elevs,
                  vals):
    """
    :param x0: The vector containing the model parameters
    
    :param elevs: Elevations at which the observations were made

    :param vals: The observed values 
    """
    c , fsin , fcos = x0
    return vals - HookeModel( elevs, c , fsin , fcos)

def MkHookeModel(a, 
                 b,
                 c):
    """
    Make a function which is a Hooke model with specific parameters
    """
    
    return lambda e : HookeModel(e, 
                                 a, 
                                 b, 
                                 c)

def fitHooke(d):
    """

    :param d: List of observations in format (elevation, value)

    """
    elevs=[x[0] for x in d]
    obs=[x[1] for x in d]
    res=leastsq(HookeModelFit,
                (0.0, 0.0, 0.0),
                (elevs, obs))    
    return res[0]

def analyse(fnamein):
    d=loadData(fnamein)
    for z in range(4,22):
        fit=fitHooke(d[z])
        print "Coefficients for z%i are c=%g, fsin=%g, fcos=%g" % (z,
                                                                   fit[0],
                                                                   fit[1],
                                                                   fit[2])
        pylab.clf()
        pylab.scatter([x[0] for x in d[z]], 
                      [x[1] for x in d[z]])
        f=MkHookeModel(*fit)
        pylab.plot(numpy.arange(0,90), 
                   f(numpy.arange(0,90)))
        pylab.savefig("plots/hookemodel-z%i.png" % z)
        
        
        
        
        
