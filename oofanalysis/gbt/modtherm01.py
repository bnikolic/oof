# Bojan Nikolic
# $Id: modtherm01.py,v 1.5 2006/02/19 18:03:26 bnikolic Exp $
#
# Investigate thermal effects

import os
import pyfits
import oofplot
import pyplot
import oofcol

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

scanlist =     [ 22,   52, 61, 70, 79, 88, 97, 106, 115, 124, 133, 142, 151, 160]

scanlist =     [ 22,   52, 61, 70,  106, 115, 124, 133, 142, 151, 160, 169, 178, 200, 209 , 218]

def PrintPars(projname, zmax=5):

    dirin = "oofout%s" % projname
    pointd= pyfits.open("thermdata/pointing.fits")[1].data

    def GetScanR(i):
        return (pointd.field("scanno")==i).argmax()

    def GetTAz(scanno):
        i = GetScanR(scanno)
        return pointd.field("lpcaz")[i] + pointd.field("dynaz")[i]

    def GetTEl(scanno):
        i = GetScanR(scanno)
        return pointd.field("lpcel")[i] + pointd.field("dynel")[i]
    
    def GetZP(parname):
        return oofcol.getpar(thisdir,
                      "offsetpars.fits",
                      parname,
                      parcol="ParName",
                      valcol="ParValue")

    res = []
    for s in scanlist:
        thisdir= os.path.join(dirin, "s%i-l-db-000/z%i" % (s, zmax))
        print "%i\t%g\t%g \t\t %g\t%g"   %  ( s,
                                              GetTAz(s),
                                              GetZP("z3"),
                                              GetTEl(s),
                                              GetZP("z5"))
        res.append( (s,
                     GetTAz(s),
                     GetZP("z3"),
                     GetTEl(s),
                     GetZP("z5")))
    return res

        

        

        
    
    


