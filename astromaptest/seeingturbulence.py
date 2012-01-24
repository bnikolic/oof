# Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
# Initial version January 2012
# 
"""
Make some simulations of astronomical seeing using turbulenent phase screens
"""
import numpy 

from localsetup import *

import pybnlib
import pyplot
import pyoof
import pybnmin1
import ooffitconv
import implot



thickscreen_name="/home/bnikolic/d/n/prog/main/astromaptest/temp/test_screen_513.fits"
m1=pyplot.FitsMapLoad(thickscreen_name,1)
m2=pyplot.MapSubset(m1, 0, 128, 0, 128)

def mkAmp(npix,
          radius=0.5,
          x0=0,
          y0=0):
    """
    """
    m=pyplot.Map(npix, npix)
    pyplot.MkRectCS(m, 
                    1,
                    1)
    pfn=pybnlib.TopHatDD()
    pfn.radius=radius
    pfn.x0=x0
    pfn.y0=y0
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
        m2=pyplot.MapSubset(m1, o, o+128, 0, 128)    
        m2.mult(0.15)
        implot.plotmap(m2, transf=2, 
                       colmap="heat",
                       fout="plots/screen-seq-%03i.png/PNG" % o)

    implot.plotmap(acc, transf=2, 
                   colmap="heat",
                   fout="plots/psf-accum.png/PNG")

def SHil(o=0):
    """
    Illustrate Shack-Hartman principle
    """
    m2=pyplot.MapSubset(m1, o, o+128, 0, 128)    
    m2.mult(0.03)
    mres=pyplot.Map(128,128)
    implot.plotmap(m2, colmap="heat", fout="plots/sh-screen-phase.png/PNG")
    implot.plotmap(ma, colmap="heat", fout="plots/sh-screen-amplitude.png/PNG")
    ff.FFTAmpPh_Power(ma, m2, mres)
    implot.plotmap(mres, transf=2,colmap="heat", fout="plots/sh-psfwhole.png/PNG")

    ma2=mkAmp(128, radius=0.2)
    implot.plotmap(ma2, colmap="heat", fout="plots/sh-screen-amplitude-l1.png/PNG")
    ff.FFTAmpPh_Power(ma2, m2, mres)
    implot.plotmap(mres, transf=2,colmap="heat", fout="plots/sh-psfl1.png/PNG")

    ma2=mkAmp(128, radius=0.1)
    implot.plotmap(ma2, colmap="heat", fout="plots/sh-screen-amplitude-l2.png/PNG")
    ff.FFTAmpPh_Power(ma2, m2, mres)
    implot.plotmap(mres, transf=2,colmap="heat", fout="plots/sh-psfl2.png/PNG")

    for i in range(7):
        for j in range(7):
            y0=-0.4+0.2*j
            ma2=mkAmp(128, radius=0.1, 
                      x0=-0.4+0.2*i,
                      y0=y0)
            print y0
            implot.plotmap(ma2, colmap="heat", fout="plots/sh-screen-amplitude-ll%i-%i.png/PNG" % (i,j))
            ff.FFTAmpPh_Power(ma2, m2, mres)
            implot.plotmap(mres, transf=0,colmap="heat", fout="plots/sh-psfll-%i-%i.png/PNG" % (i,j), 
                           contours=implot.MkSynthesisContours(mres, step=0.5, nlevels=4),
                           bbox=[40,88,40,88])
            
    
    
    
    



