# Bojan Nikolic
# $Id: analysebump.py,v 1.1 2006/04/01 17:44:04 bnikolic Exp $
#
#

import os
import math

import ooffitconv
import oofplot
import implot
import pyplot


def PlotHB():

    oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s42-l-db-000/z5/fitpars.fits",
                          "plots/measuredhalfbumpphase.eps/CPS")

    return oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s42-l-db-000/z5/fitpars.fits",
                                 "plots/measuredhalfbumpphase.png/PNG")


def PlotNBAvg():

    m1=oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s24-l-db-000/z5/offsetpars.fits",
                             "temp/t.png/PNG")
    m2=oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s51-l-db-000/z5/offsetpars.fits",
                             "temp/t.png/PNG")

    m1.add(m2)
    m1.mult(0.5)

    implot.plotmap( m1,
                    "plots/avgnobump.png/PNG",
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=[-2,2])

    return m1

def PlotD2():

    mb=PlotHB()
    mnobump=PlotNBAvg()
    mnobump.mult(-1)
    
    mb.add(mnobump)
    implot.plotmap( mb,
                    "plots/diff.png/PNG",
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=[-2,2])
    return mb
    
    
def PlotDiff():

    m1=oofplot.PlotZernFile( "bump/rhbumphalfoof.fits" , "test.png/PNG" )
    m2=PlotD2()

    m1.mult(1)
    m2.add(m1)

    i1    = oofplot.PlotIllumFile( "oofoutTPTCSOOF_060330/s42-l-db-000/z5/fitpars.fits",
                                   "temp/amp.png/PNG")

    print "WRMS: " , pyplot.MapRMS(m2, i1 )

    implot.plotmap( m2,
                    "plots/halfbumpdiff.png/PNG",
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=[-2,2])
