# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>.
# The initial versions of this file appeared in 2005 and was
# signficantly extended in 2006. 
#
# Updated in 2010, and also deleted a lot of the GBT specific old code
"""
Tools for analysis of scans across the Moon and similar data used to
constrain error correlation scales on radio telescopes
"""

import math

import numpy
from matplotlib import pylab

import pyplot
import pybnlib
import pyoof
import implot
    
def mkALMAAperture(npix=512,
                   phaserms=0.5,
                   errscale=1,
                   ant="vertex",
                   justPhase=False):
    """
    Make an aperture plane amplitude-phase map appropriate for an ALMA
    12m telescope

    :note: phaserms and errscale can take lists of as parameters. In
    this case it is assumed that there are multiple error distribution
    present on the telescope. Example:
    
    >>> mphase = mkALMAAperture(phaserms=[1.0, 1.0], 
                                errscale=[1.0, 0.1], 
                                justPhase=True)
    
    Has two distributions, one with scale of 1m and the other with
    scale of 10cm.

    :param phaserms: Magnitude of errors, expressed as unweighted,
    *wavefront* error in radian

    :param errscale: Correlation length scale of errors in units of m

    """
    tel=pyoof.MkALMA()

    mphase=pyoof.MkApMap(tel,
                         npix,
                         2.0)    

    # Size of one pixel (in x direction, but they will be the same
    # size in both)
    pxscale=mphase.cs.x_pxtoworld(1,0)-mphase.cs.x_pxtoworld(0,0)

    if type(phaserms) is not list:
        phaserms=[phaserms]
        errscale=[errscale]
    else:
        if len(phaserms) != len(errscale):
            raise "The magnitude of errors and error scale lists must be of same length"
        
    mtemp=pyoof.MkApMap(tel,
                        npix,
                        2.0)    
    for _rms, _scale in zip(phaserms, errscale):
        pyplot.CorrGaussGauss(mtemp, 
                              1.0, 
                              pxscale/_scale*npix)
        mtemp.mult(_rms/pyplot.MapRMS(mtemp))
        mphase.add(mtemp)

    if justPhase:
        return mphase
        
    mamp=pyoof.MkApMap(tel,
                       npix,
                       2.0)    

    ilmod=pyoof.GaussAmpMod( tel, mamp)
    ilmod.SetSigma(0.3)
    ilmod.Calc(mamp)  
    ALMABlockDict[ant](mamp)

    return mphase, mamp

def supportWidthVertex(r):
    """
    Calculate the width of the support leg for Vertex
    
    :param r: Radius from centre of dish in metres
    """
    r=r*1e3
    rblock=[375.0, 3897.0, 4197.0, 4497.0, 4797.0, 5097.0, 5397.0, 5697.0, 6000.0];
    hblock=[40.0, 40.0, 46.1, 48.9, 58.7, 60.8, 66.5, 72.4, 78.3,];
    k1=0
    for k in range(len(rblock)-1):
        if rblock[k]<r:
            k1=k
    delta=(hblock[k1+1]-hblock[k1])/(rblock[k1+1]-rblock[k1])
    return (hblock[k1] + (r-rblock[k1])*delta)*1e-3

def ALMABlock(m,
              vblock=True,
              blockf=supportWidthVertex):
    """
    Mask areas of the antenna blocked by the support structure etc.
    
    :param vblock: True for antennas with + type support, False for
    antennas with X type support
    
    :param blockf: Width of the support structure as a function of
    radius from centre (note that this is passed in as a function)
    """
    
    for i in range(m.nx):
        for j in range(m.ny):
            x=m.cs.x_pxtoworld(i,j)
            y=m.cs.y_pxtoworld(i,j)
            r=(x**2+y**2)**0.5
            # Outside primary or inside secondary
            if r>6.0 or r<0.75/2:
                m.set(i,j,0)

            if vblock:
                rq=min(math.fabs(x), math.fabs(y))
            else:
                rq=min(math.fabs(x) + math.fabs(y),
                       math.fabs(x) - math.fabs(y)) / 2.0**0.5
            if rq < blockf(r):
                m.set(i,j,0);

ALMABlockDict= {"vertex":
                    lambda m: ALMABlock(m, vblock=True,
                                        blockf=supportWidthVertex)}


                  
def MkMoon(m,
           Cm=0):
    """
    A rough function to generate a simulated Moon
    """

    # moon radius 15 arcmin
    mradius=15 * math.pi / 180 / 60

    moonfn  =  pybnlib.TaperedTopHatDD()
    moonfn.radius  =  mradius
    moonfn.Cm = Cm
    pyplot.WorldSet( m , moonfn)

            

                


def mkMoonSim(mbeam,
              Cm=0):
    """
    Make a simulation of a Moon observation

    :param mbeam: Map of the telescope beam
    
    :param Cm: The softening parameter. See A. Greve et al, A&A 1998

    :return: The simulated map
    """
    mmoon = pyplot.Clone(mbeam)
    MkMoon(mmoon, 
           Cm=Cm)

    res=pyplot.FFTConvolve(mbeam,
                           mmoon)

    return res

def mapCut(mbeam):
    """
    Create a cut through a map
    """
    pxscale=mbeam.cs.x_pxtoworld(1,0)-mbeam.cs.x_pxtoworld(0,0)
    ymid= int(mbeam.ny*0.5)
    dx, fnu= [], []
    for i in range(mbeam.nx):
        dx.append((i-mbeam.nx*0.5)*pxscale)
        fnu.append(mbeam.getv(i,ymid))
    return numpy.array(dx), numpy.array(fnu)
        
    


if 1:
    # Creates a pair of maps which represent the the aperture plane
    # phase and amplitude distributions
    mphase, mamp = mkALMAAperture(phaserms=[0.4, 0.4], 
                                  errscale=[1.0, 0.4])
    # Plot the phase map
    implot.plotmap(mphase, transf=0, colmap="heat")
    # Plot the amplitude
    implot.plotmap(mphase, transf=0, colmap="heat")
    # Create the object that transforms the aperture plane
    # distribution to far field. The second parameter is the
    # wavelenght of the radiation
    farf= pyoof.FarF(mamp, 
                     3.5e-3)
    # Create a map to store the far field pattern in
    mbeam=pyplot.Map(512,512)
    # Compute the far-field power pattern
    farf.Power(mamp, mphase, mbeam)
    # Plot the beam as on log-scale (second parameter, it has the same
    # meaning as the convention in PGPLOT)
    implot.plotmap(mbeam, transf=1, colmap="heat")
    # Convolve with a Moon simulation
    mb3=mkMoonSim(mbeam)
    # Plot the beam as on log-scale
    implot.plotmap(mb3, transf=1, colmap="heat")
    
