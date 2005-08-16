# Bojan Nikolic
# $Id: oofreduce.py,v 1.3 2005/08/16 18:00:58 bnikolic Exp $
#
# Main OOF reduction script

oofreducever = r"$Revision: 1.3 $"

import pyfits

import pyplot
import pyoof


def MkTel(fnamein):

    "Returns the telescope geometry of the telescope specified in the file"

    telname= pyfits.open(fnamein)[0].header["telesc"]

    return pyoof.TelSwitch(telname)


def GetObsWaveL(fnamein):

    "Return the obseving wavelength"

    filein = pyfits.open(fnamein)
    
    return  3e8 / filein[0].header["freq"]


def MkMapResDS(fnamein,
               extno,
               skymapsample,
               fwhm=2.0,
               extent=4):

    ds=pyplot.LoadFITSDS(fnamein, extno+1)

    mapds= pyoof.MapToResidualDS( ds, skymapsample, fwhm, extent)

    return mapds

def MkPhaseScreen(fnamein, i, apmapsample):

    fin = pyfits.open(fnamein)

    tel = MkTel(fnamein)

    dz  = float(fin[i].header["dz"])

    ps  = pyoof.ObsDefocus( tel, apmapsample , dz)

    return ps


def LoadOCData( fnamein,
                telgeo,
                skymapsample,
                apmapsample,
                oc,
                *args):

    fin = pyfits.open(fnamein)
    
    for i in range(1, len(fin) ):
        mapres= MkMapResDS( fnamein, i , skymapsample)
        ps    = MkPhaseScreen( fnamein, i, apmapsample)

        mapres.thisown=0
        ps.thisown=0
        oc.AddObs(mapres, ps)
                
    
def MkObsCompare(fnamein,
                 npix=128,
                 nzern=6,
                 oversample=2.0
                 ):

    "Make an ObsCompare object from the given file"

    tel = MkTel(fnamein)

    wavel= GetObsWaveL(fnamein)

    aperture = pyoof.MkSimpleAp ( tel,
                                  wavel,
                                  npix,
                                  nzern,
                                  oversample)

    aperture.thisown=0
    
    oc= pyoof.ObsCompare( aperture,
                          aperture.getphase() );

    skymapsample=oc.Beam();

    
    # now just load the observations and done...
    #
    LoadOCData( fnamein, tel, skymapsample, aperture.getphase(), oc)

    return oc
    






