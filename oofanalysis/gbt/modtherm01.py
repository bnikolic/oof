# Bojan Nikolic
# $Id: modtherm01.py,v 1.2 2006/02/18 20:40:02 bnikolic Exp $
#
# Investigate thermal effects

import os

import oofplot
import pyplot

def PlotSfcs():

    def plot ( sdate, sno ):

        zfin = "oofout%s/s%i-l-db-000/z5/offsetpars.fits" % ( sdate, sno )
        oofplot.PlotZernFile( zfin,
                              "plots/sfc%s-%i.eps/CPS" % (sdate, sno) )
        oofplot.PlotZernFile( zfin,
                              "plots/sfc%s-%i.png/PNG" % (sdate, sno) )


    for sno in [ 83 , 91, 135, 143, 187, 195]:
        plot ("1130" , sno)
        plot ("1130" , sno)

def MRMS( sdate, sno):

    indir= "oofout%s/s%i-l-db-000/z5" % (sdate, sno)
    
    phasef= oofplot.PlotZernFile( os.path.join(indir ,
                                               "fitpars.fits"),
                                  "plots/measuresfc.eps/CPS")
    ilumf = oofplot.PlotIllumFile( os.path.join(indir ,
                                                "fitpars.fits"),
                                   "plots/measureamp.eps/CPS")

    print pyplot.MapRMS(phasef, ilumf)
    
    


