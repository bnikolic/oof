# Bojan Nikolic
# $Id: oofreduce.py,v 1.13 2005/09/06 00:55:38 bnikolic Exp $
#
# Main OOF reduction script

oofreducever = r"$Revision: 1.13 $"

import math
import os

import pyfits

import pybnmin1
import bnmin1io

import pyplot
import pyoof
import iofits4
import oofcol


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
               fwhm=1.0,
               extent=2,
               dsreverse=False):

    ds=pyplot.LoadFITSDS(fnamein, extno+1)

    ds.thisown=0

    if  dsreverse:
        print "Reversing !"
        #pyplot.InvertDS(ds)
        
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
                fwhm=1.0, extent=2.0,
                dsreverse=False):

    fin = pyfits.open(fnamein)
    
    for i in range(1, len(fin) ):
        mapres= MkMapResDS( fnamein, i , skymapsample,
                            fwhm=fwhm, extent=extent,
                            dsreverse=dsreverse)
        ps    = MkPhaseScreen( fnamein, i, apmapsample)

        mapres.thisown=0
        ps.thisown=0
        oc.AddObs(mapres, ps)
                

def MkFF ( fnamein,
           apphase):

    wavel = GetObsWaveL(fnamein)

    telname= pyfits.open(fnamein)[0].header["telesc"]

    if telname == "GBT":

        recvname=None 
        try:
            recvname= pyfits.open(fnamein)[0].header["recv"]
        except:
            print "No recv keyword... assuming Q band!!"
            recvname= "qunbal"
            
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
                 oversample=2.0,
                 ds_fwhm=1.0,
                 ds_extent=2.0,
                 dsreverse=False
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
    LoadOCData( fnamein, tel, skymapsample, aperture.getphase(), oc,
                fwhm=ds_fwhm, extent=ds_extent, dsreverse=dsreverse)

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

def FitStatTab(m):

    "Creat a fits table with fits details "

    chisquaredfinal = m.ChiSquared()

    ftable=iofits4.FnParTable(locals(),
                              r"$Id: oofreduce.py,v 1.13 2005/09/06 00:55:38 bnikolic Exp $")
    return ftable

def Red(obsfilename,
        prefdirout="oofout",
        extrafit= [],
        extraic = [],
        nzmax=7,
        npix=128,
        oversample=2.0,
        ds_fwhm=1.0,
        ds_extent =2.0,
        dsreverse=False):

    "A general reduction script"

    """
    nzmax:  the maximum zernike order to go to.
    extrafit: list of parameter names to turn fitting on for
    extraic : a list of extra inititial conditions in format (parname, parvalue)
    """

    ptable=iofits4.FnParTable(locals(),
                              r"$Id: oofreduce.py,v 1.13 2005/09/06 00:55:38 bnikolic Exp $")

    dirout = oofcol.mkodir( prefdirout ,
                            oofcol.basename(obsfilename))

    #The last recorded fit file goes into this variable to restart the
    #minimisation with higher number of Zernike from that point
    lastfitf= None
    
    for nzern in range(1, nzmax+1):

        print "Nzern = %i " % nzern

        cdirout = os.path.join(dirout, "z%i" % nzern )

        oc=MkObsCompare(obsfilename, nzern=nzern,
                        npix=npix, oversample=oversample,
                        ds_fwhm=ds_fwhm,
                        ds_extent=ds_extent,
                        dsreverse=dsreverse)

        lmm=pybnmin1.LMMin(oc.downcast())
        lmm.ftol=1e-4
        
        m1 = pybnmin1.ChiSqMonitor()
        m1.thisown = 0
        lmm.AddMon( m1)

        for pname in extrafit :
            lmm.getbyname(pname).dofit=1

        if lastfitf:
            bnmin1io.FLoad(lmm, lastfitf)
        else:
            for parname, parvalue in extraic:
                lmm.getbyname(parname).setp(parvalue)
            
        lmm.solve()

        fitname = os.path.join(cdirout, "fitpars.fits")
        bnmin1io.FSave(lmm, fitname)
        fstattab= FitStatTab(lmm)        

        #Save the covariance matrix
        bnmin1io.CVSave(lmm,
                        os.path.join(cdirout, "cvmatrix")
                        )        

        pyoof.WriteAperture(oc,
                            "!"+os.path.join(cdirout, "aperture.fits"))

        pyoof.WriteBeams(oc,
                         "!"+os.path.join(cdirout, "fitbeams.fits"))

        oc.GetAperture().ZeroTilt();
        pyoof.WriteAperture(oc,
                            "!"+os.path.join(cdirout, "aperture-notilt.fits"))

        # Save the fits file with information about the fit
        iofits4.Write( [pyfits.PrimaryHDU() ,
                        ptable,
                        fstattab,
                        ],
                       os.path.join(cdirout, "fitinfo.fits") ,
                       overwrite=1)

        # Write out perfect beams:
        oc=MkObsCompare(obsfilename, nzern=1,
                        npix=npix, oversample=oversample,
                        ds_fwhm=ds_fwhm,
                        ds_extent=ds_extent,
                        dsreverse=dsreverse)
        
        lmm=pybnmin1.LMMin(oc.downcast())
        bnmin1io.FLoad(lmm, fitname,
                       silent=True)
        pyoof.WriteBeams(oc,
                         "!"+os.path.join(cdirout, "perfectbeams.fits"))        


        lastfitf=fitname

        

        


    

        
    






