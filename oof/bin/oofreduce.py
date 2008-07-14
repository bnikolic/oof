# Bojan Nikolic <bojan@bnikolic.co.uk>, <bn204@mrao.cam.ac.uk>,
# <b.nikolic@mrao.cam.ac.uk>
#
# Main OOF reduction script

oofreducever = r"(CVS-based revnos obsoleted)"

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

def GetBeamSeparation(fnamein):
    "Return the beam separation in arcsec"
    filein = pyfits.open(fnamein)
    try:
        beamsep = filein[0].header['CHOPTHR']
    except:
        print "CHOPTHR not found in header. Assuming Q-band value."
        beamsep = 57.8
    return beamsep

def GetObsWaveL(fnamein):

    "Return the observing wavelength"

    filein = pyfits.open(fnamein)
    
    return  3e8 / filein[0].header["freq"]

def GetRecvName(fnamein):

    "Return the name of the receiver in use"

    fin = pyfits.open(fnamein)

    if fin[0].header.has_key( "recv") :
        return fin[0].header["recv"]
    else:
        # Guess
        if fin[0].header["telesc"] == "GBT":
            wavel = GetObsWaveL(fnamein)
            if wavel < 0.005 :
                return  "mustang"
                print "No recv keyword... assuming mustang!!"
            else:
                return "qunbal"
                print "No recv keyword... assuming Q band!!"
        else:
            return None
    

def MkMapResDS(fnamein,
               extno,
               skymapsample,
               fwhm=1.0,
               extent=2):

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
                fwhm=1.0,
                extent=2.0):

    fin = pyfits.open(fnamein)
    
    for i in range(1, len(fin) ):
        mapres= MkMapResDS( fnamein, i , skymapsample,
                            fwhm=fwhm, extent=extent)
        
        ps    = MkPhaseScreen( fnamein, i, apmapsample)

        mapres.thisown=0
        ps.thisown=0
        oc.AddObs(mapres, ps)
                

def MkFF ( fnamein,
           apphase):
    """
    Make the objects that calculate the far-field antenna response.
    
    :param fnamein: The name of file containing the
    observation. Parameters such as telescope and chopthorw are
    retrieved from this file

    :param apphase: The object representing the aperture-plane
    electric field distribution of the telescope.

    :returns: The Far-Field object. GC is disabled on this object
    since normally it will be passed to C++ objects that will want to
    own it.
    """

    wavel = GetObsWaveL(fnamein)

    telname= pyfits.open(fnamein)[0].header["telesc"]

    if telname == "GBT":

        recvname=GetRecvName(fnamein)

        if recvname == "qunbal":
            beamSeparationArcsec = GetBeamSeparation(fnamein)            
            ff = pyoof.ChoppedFF( apphase , wavel)
            ff.hchop = -beamSeparationArcsec *  math.pi / 180.0 / 3600
        elif recvname == "Ka":
            beamSeparationArcsec = GetBeamSeparation(fnamein)            
            ff = pyoof.ChoppedFF( apphase , wavel)
            ff.hchop = +beamSeparationArcsec *  math.pi / 180.0 / 3600
        elif recvname == "mustang":
            ff = pyoof.FarF(apphase, wavel)            
        else:
            raise "Unknown receiver/GBT: " + recvname
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
                 nobs=1
                 ):
    """
    Makes an ObsCompare object from the given file. This object allows
    comparison of observations to models of the far-field response.
    
    :param nobs: if greater than one setup separate models for each
    observation in the set
    """

    tel=MkTel(fnamein)
    wavel=GetObsWaveL(fnamein)
    recv= GetRecvName(fnamein)

    if recv=="mustang":
        if nobs==1:
            aperture=pyoof.MkMUSTANGAp(tel,
                                       wavel,
                                       npix,
                                       nzern,
                                       oversample)
        else:
            aperture=pyoof.MkMgMltiAmpAp(tel,
                                         wavel,
                                         npix,
                                         nzern,
                                         oversample,
                                         nobs)
    else:
        aperture = pyoof.MkSimpleAp ( tel,
                                      wavel,
                                      npix,
                                      nzern,
                                      oversample)

    aperture.thisown=0

    obsff  = MkFF (fnamein, 
                   aperture.getphase())
    
    oc= pyoof.ObsCompare(aperture,
                         aperture.getphase(),
                         obsff);

    skymapsample=oc.Beam();

    
    # now just load the observations and done...
    #
    LoadOCData(fnamein,
               tel,
               skymapsample,
               aperture.getphase(),
               oc,
               fwhm=ds_fwhm,
               extent=ds_extent)
    return oc

def SimBeamDS(obsfilename, 
              beamfilename):
    """
    Simulate the data series given observing pattern and beam shape
    
    :param obsfilename: File name containing definition of the
    observation being simulated -- this defines telescope, positions
    where beam has been measured, etc ("FNU" column obviously can be
    zero).

    :param beamfilename: FITS file containing beams to simulate
    """
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
                              r"$Id: oofreduce.py,v 1.16 2005/09/12 01:07:35 bnikolic Exp $")
    return ftable

def OffsetFname(fnamein):

    "Return the name of the offset file if it exists"

    """
    The telescope may already have a surface correction dialed
    in... take that into account here.
    """

    fbasename=fnamein[:-5]

    try1 = fbasename+"-offset.fits"
    if os.access(try1, os.F_OK) : return try1
    else: return None

def RedOrder(obsfilename,
             dirout,
             extrafit= [],
             ic = [],
             zorder=5,
             npix=128,
             oversample=2.0,
             ds_fwhm=1.0,
             ds_extent =2.0,
             ptable=None):
    """Reduce OOF observation at single maximum order of Zernikes
    (c.f. function Red() which steps through a number of orders)

    :param obsfilename: Filename containing the observed data 
    
    :param dirout: Directory where to place reduction output
    
    :param extrafit: List of parameter names which may not be fit by
    default but the user wants to turn fitting on for

    :param ic: a list of extra inititial conditions in format
    (parname, parvalue) or a filename of a fit file containing the
    initial conditions

    :param zorder: Maximum Zernike Order to fit for
    
    :param ptable: FITS table of fit parameters to save in output (if
    None, locals of this function are used)

    :returns: Filename of the file containing the fit
    """
    wavel = GetObsWaveL(obsfilename)
    
    oc=MkObsCompare(obsfilename, 
                    nzern=zorder,
                    npix=npix, 
                    oversample=oversample,
                    ds_fwhm=ds_fwhm,
                    ds_extent=ds_extent)

    lmm=pybnmin1.LMMin(oc.downcast())
    lmm.ftol=1e-4
    
    m1 = pybnmin1.ChiSqMonitor()
    m1.thisown = 0
    lmm.AddMon( m1)

    for pname in extrafit :
        lmm.getbyname(pname).dofit=1

    if type(ic) == str :
        bnmin1io.FLoad(lmm, ic)
    else:
        for parname, parvalue in ic:
            lmm.getbyname(parname).setp(parvalue)
            
    lmm.solve()

    fitname = os.path.join(dirout, "fitpars.fits")
    bnmin1io.FSave(lmm, fitname)
    fstattab= FitStatTab(lmm)        

    #Save the covariance matrix
    bnmin1io.CVSave(lmm,
                    os.path.join(dirout, "cvmatrix")
                    )        

    pyoof.WriteAperture(oc,
                        "!"+os.path.join(dirout, "aperture.fits"))

    pyoof.WriteBeams(oc,
                     "!"+os.path.join(dirout, "fitbeams.fits"))

    oc.GetAperture().ZeroTilt();
    pyoof.WriteAperture(oc,
                        "!"+os.path.join(dirout, "aperture-notilt.fits"))

    hdulist = pyfits.open(os.path.join(dirout, "aperture-notilt.fits"),mode='update')
    for ext in range(0,2):
        prihdr = hdulist[ext].header
        prihdr.update('wave',wavel,'wavelength (m), floating value')
    hdulist.flush()

    # Save the fits file with information about the fit
    if ptable is None:
        ptable=iofits4.FnParTable(locals(),
                                  " ")

    iofits4.Write( [pyfits.PrimaryHDU() ,
                    ptable,
                    fstattab,
                    ],
                   os.path.join(dirout, "fitinfo.fits") ,
                   overwrite=1)
        

    # Write out offset aperture and beams if exist
    if OffsetFname(obsfilename):
        bnmin1io.FAdd(lmm, OffsetFname(obsfilename), silent=True)
        bnmin1io.FSave(lmm,
                       os.path.join(dirout, "offsetpars.fits"))
        pyoof.WriteAperture(oc,
                            "!"+os.path.join(dirout, "aperture-offset.fits"))
        pyoof.WriteBeams(oc,
                         "!"+os.path.join(dirout, "offsetbeams.fits"))
            
        
    # Write out perfect beams:
    oc=MkObsCompare(obsfilename, nzern=1,
                    npix=npix, oversample=oversample,
                    ds_fwhm=ds_fwhm,
                    ds_extent=ds_extent)
        
    lmm=pybnmin1.LMMin(oc.downcast())
    bnmin1io.FLoad(lmm, fitname,
                   silent=True)
    pyoof.WriteBeams(oc,
                     "!"+os.path.join(dirout, "perfectbeams.fits"))            
    return fitname
             
def Red(obsfilename,
        prefdirout="oofout",
        extrafit= [],
        extraic = [],
        nzmax=7,
        npix=128,
        oversample=2.0,
        ds_fwhm=1.0,
        ds_extent =2.0):

    "A general reduction script"

    """
    See also documentation of RedOrder

    nzmax:  the maximum zernike order to go to.
    extrafit: list of parameter names to turn fitting on for
    extraic : a list of extra inititial conditions in format (parname, parvalue)
    """

    ptable=iofits4.FnParTable(locals(),
                              r"$Id: oofreduce.py,v 1.16 2005/09/12 01:07:35 bnikolic Exp $")

    dirout = oofcol.mkodir( prefdirout ,
                            oofcol.basename(obsfilename))

    #The last recorded fit file goes into this variable to restart the
    #minimisation with higher number of Zernike from that point
    lastfitf=extraic

    for nzern in range(1, nzmax+1):

        print "Nzern = %i " % nzern

        cdirout = os.path.join(dirout, "z%i" % nzern )

        lastfitf=RedOrder(obsfilename,
                          cdirout,
                          extrafit=extrafit,
                          ic=lastfitf,
                          zorder=nzern,
                          npix=npix, 
                          oversample=oversample,
                          ds_fwhm=ds_fwhm,
                          ds_extent=ds_extent,
                          ptable=ptable)
        

def InvertDSFile (fnamein, fnameout ):

    "Invert the data series contained in fnamein through the origin"

    fin = pyfits.open(fnamein)

    for i in range(1, len(fin) ):
        dx=fin[i].data.field("dx")
        dx *= -1

        dy=fin[i].data.field("dy")
        dy *= -1

    iofits4.Write(fin , fnameout , overwrite=1)
    pass


    

        
    






