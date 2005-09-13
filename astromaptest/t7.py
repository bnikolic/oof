# Bojan Nikolic
# Analyse OOF data from 0317
#
# $Id: t7.py,v 1.2 2005/09/13 19:07:01 bnikolic Exp $


datadir="/home/bnikolic/data/gbtoof/TPTCSOOF_050317"

import os
import oofreduce
import pyfits
import oofplot
import oofcol
import bnmin1io


scannos   = [ 110 , 143, 167, 192, 215, 258 ]

def mkfname(sno):
    "Return full file name of given the scan number"

    return os.path.join( datadir,
                         "s%i-l-db.fits" % sno )


def Red():
    for sno in scannos:

        oofreduce.Red(mkfname(sno),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5)


def plot(nz=5):
    
    for sno in scannos:
        oofplot.PlotDir("oofout/s%i-l-db-000/z%i" % ( sno , nz ),
                        bbox=[ -1e-3, 1e-3, -1e-3, 1e-3])


def cmppars( parname , nz=5 ):

    "Figure out how parameters are changing with elevation"
    
    for sno in scannos:
        dirin="oofout/s%i-l-db-000/z%i" % ( sno , nz ) 
        print ( sno,
                oofcol.direlev(dirin) ,
                bnmin1io.FGetPar(os.path.join(dirin,  "fitpars.fits"),
                                 parname))
        
        

        
        
