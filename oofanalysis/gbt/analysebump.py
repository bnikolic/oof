# Bojan Nikolic
# $Id: analysebump.py,v 1.3 2006/04/26 09:23:10 bnikolic Exp $
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


def BumpPlot(m,fnameout):

    implot.plotmap( m,
                    os.path.join("plots/bump", fnameout+".png/PNG"),
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=[-2,2])

    implot.plotmap( m,
                    os.path.join("plots/bump", fnameout+".cps/CPS"),
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=[-2,2])
    
def PlotNBAvg():

    m1=oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s24-l-db-000/z5/offsetpars.fits",
                             "temp/t.png/PNG")
    m2=oofplot.PlotZernFile( "oofoutTPTCSOOF_060330/s51-l-db-000/z5/offsetpars.fits",
                             "temp/t.png/PNG")

    m1.add(m2)
    m1.mult(0.5)

    BumpPlot(m1, "avgnobump")


    return m1

def PlotBump():

    m1=oofplot.PlotZernFile( "bump/rhbumphalfoof.fits",
                             "temp/t.png/PNG")
    m1.mult(-1)
    BumpPlot(m1, "bumpdialed")

def PlotD2():

    mb=PlotHB()
    mnobump=PlotNBAvg()
    mnobump.mult(-1)
    
    mb.add(mnobump)

    BumpPlot(mb, "bumpbestest")

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

def ClosurePlot():

    m1=oofplot.PlotZernFile( "oofout0411/s471-l-db-000/z5/fitpars.fits" ,
                             "plots/closure/daybefore.png/PNG" ,
                             phaserange=[-2,2])

    m1=oofplot.PlotZernFile( "oofout0411/s471-l-db-000/z5/fitpars.fits" ,
                             "plots/closure/daybefore.eps/CPS" ,
                             phaserange=[-2,2])    

    m2=oofplot.PlotZernFile( "oofout0411/s492-l-db-000/z5/fitpars.fits" ,
                             "plots/closure/dayafter.png/PNG" ,
                             phaserange=[-2,2])
    m2=oofplot.PlotZernFile( "oofout0411/s492-l-db-000/z5/fitpars.fits" ,
                             "plots/closure/dayafter.eps/CPS" ,
                             phaserange=[-2,2])    

    i1    = oofplot.PlotIllumFile("oofout0411/s471-l-db-000/z5/fitpars.fits" ,
                                   "temp/amp.png/PNG")

    print "WRMS before: " , pyplot.MapRMS(m1, i1 )
    print "WRMS after:  " , pyplot.MapRMS(m2, i1 )    
