# Bojan Nikolic
# $Id: oofreduce.py,v 1.7 2005/08/18 23:52:32 bnikolic Exp $
#
# Main OOF reduction script

oofreducever = r"$Revision: 1.7 $"

import math

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

    ds.thisown=0

    mapds= pyoof.MapToResidualDS( ds, skymapsample, fwhm, extent)

    return mapds

def MkPhaseScreen(fnamein, i, apmapsample):

    fin = pyfits.open(fnamein)

    tel = MkTel(fnamein)

    dz  = float(fin[i].header["dz"])
    print dz

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
            ff.hchop = -57.8 *  math.pi / 180.0 / 3600
        else:
            raise "Unknown receiver/GBT: " + recvnema
    else:
        ff = pyoof.FarF(apphase, wavel)

    ff.thisown=0        
    return  ff


def MkSampleAp(fnamein,
               npix=128,
               oversample=2.0):
    
    tel = MkTel(fnamein)

    wavel= GetObsWaveL(fnamein)

    return pyoof.MkSimpleAp ( tel,
                              wavel,
                              npix,
                              0,
                              oversample)    
    
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

def SimBeamDS(obsfilename, beamfilename):

    "Return the data series corresponding the simulated beams"
              

    obsfile=pyfits.open(obsfilename)

    res=[]

    for i in range(1, len(obsfile)):

        skym=pyplot.FitsMapLoad(beamfilename, i)
        mkds=MkMapResDS( obsfilename, i , skym)
        res.append(mkds.MkModelDS(skym))

    return res

        
    






