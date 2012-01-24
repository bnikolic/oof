# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# Initial version January 2012
# 
"""
Make some simulations of astronomical seeing using turbulenent phase screens
"""

from localsetup import *

import pybnlib
import pyplot
import pyoof
import pybnmin1
import ooffitconv
import implot



thickscreen_name="/home/bnikolic/d/n/almawvr/py/temp/atmo_em_screen_33.fits"
m1=pyplot.FitsMapLoad(thickscreen_name,1)
m2=pyplot.MapSubset(m1, 0, 128, 0, 128)

def mkAmp(npix):
    """
    """
    m=pyplot.Map(npix, npix)
    pyplot.MkRectCS(m, 
                    1,
                    1)
    pfn=pybnlib.TopHatDD()
    pfn.radius=0.5
    pyplot.WorldSet(m,
                    pfn)
    return m

ma=mkAmp(128)
ff=pyplot.FFTFact(ma.nx, ma.ny, pyplot.FFTFact.forward)

def PSF(s, o):
    m2=pyplot.MapSubset(m1, o, o+128, 0, 128)    
    m2.mult(s)
    mres=pyplot.Map(128,128)
    ff.FFTAmpPh_Power(ma, m2, mres)
    return mres

def PSFSeq():
    acc=pyplot.Map(128,128)
    for o in range(0,200,10):
        mm=PSF(0.15,o*3)
        implot.plotmap(mm, transf=2, 
                       colmap="heat",
                       fout="plots/psf-seq-%03i.png/PNG" % o)
        acc.add(mm)
    implot.plotmap(acc, transf=2, 
                   colmap="heat",
                   fout="plots/psf-accum.png/PNG")



