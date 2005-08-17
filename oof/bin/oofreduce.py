# Bojan Nikolic
# $Id: oofreduce.py,v 1.5 2005/08/17 20:43:36 bnikolic Exp $
#
# Main OOF reduction script

oofreducever = r"$Revision: 1.5 $"

import pyfits

import pyplot
import pyoof


def MkTel(fnamein):

    "Returns the telescope geometry of the telescope specified in the file"

    telname= pyfits.open(fnamein)[0].header["telesc"]

    tel = pyoof.TelSwitch(telname)

    if tel == None:
        raise "Uknown telescope : " + telname

    return tel


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

    wavel = GetObsWaveL(fnamein)

    ps  = pyoof.ObsDefocus( tel, apmapsample , dz, wavel)

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
                

def MkFF ( fnamein,
           apphase):

    wavel = GetObsWaveL(fnamein)

    telname= pyfits.open(fnamein)[0].header["telesc"]

    if telname == "GBT":

        recvname= pyfits.open(fnamein)[0].header["recv"]
        if recvname == "qunbal":
            ff = pyoof.ChoppedFF( apphase , wavel)
            ff.hchop = -60 * 5e-6
        else:
            raise "Unknown receiver/GBT"
    else:
        ff = pyoof.FarF(apphase, wavel)

    ff.thisown=0        
    return  ff

    
    
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

    obsff  = MkFF (fnamein, aperture.getphase())
    
    oc= pyoof.ObsCompare( aperture,
                          aperture.getphase() ,
                          obsff);

    skymapsample=oc.Beam();

    
    # now just load the observations and done...
    #
    LoadOCData( fnamein, tel, skymapsample, aperture.getphase(), oc)

    return oc
    






