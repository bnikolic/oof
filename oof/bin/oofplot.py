# Bojan Nikolic
# $Id: oofplot.py,v 1.17 2006/04/26 10:16:48 bnikolic Exp $
#
# Various utilities for plotting OOF data

import os

import pyfits

import implot
import pyplot
import pyoof
import pybnmin1
import bnmin1io


import oofreduce
import oofcol

def PlotDir(dirnamein, bbox=None, hardcopy=False, odir="plots",
            fwhm=None , extent = None, npix= None,
            ncont=None,
            decorate=True):

    "Make all the relevant plots"

    """

    If( hardcopy) make hardcopy friendly plots

    """

    obsdsfname=  oofcol.getpar(dirnamein,  "fitinfo.fits", "obsfilename")
    npix= npix or int(oofcol.getpar(dirnamein,  "fitinfo.fits", "npix") )
    oversample= float( oofcol.getpar(dirnamein,  "fitinfo.fits", "oversample") )
    fwhm=fwhm or float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_fwhm") )
    extent=extent or float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_extent") )

    PlotDSFile( obsdsfname,
                os.path.join(dirnamein, odir),
                prefix="obsbeam",
                oversample= oversample,
                npix=npix,
                fwhm=fwhm,
                extent=extent,
                bbox=bbox,
                ncont=ncont,
                hardcopy=hardcopy,
                decorate=decorate)

    PlotSimDrizzleBeams( obsdsfname,
                         os.path.join(dirnamein, "fitbeams.fits"),
                         os.path.join(dirnamein, odir),
                         prefix="bestfitbeams",
                         bbox=bbox,
                         fwhm=fwhm,
                         extent=extent,
                         npix=npix,
                         oversample=oversample,
                         ncont=ncont,
                         hardcopy=hardcopy,
                         decorate=decorate)

    PlotSimDrizzleBeams( obsdsfname,
                         os.path.join(dirnamein, "perfectbeams.fits"),
                         os.path.join(dirnamein, odir),
                         prefix="perfectbeams",
                         bbox=bbox,
                         fwhm=fwhm,
                         extent=extent,
                         npix=npix,
                         oversample=oversample,
                         ncont=ncont,
                         hardcopy=hardcopy,
                         decorate=decorate)

    PlotAperture( os.path.join(dirnamein, "aperture-notilt.fits"),
                  os.path.join(dirnamein, odir),
                  oversample=oversample,
                  hardcopy=hardcopy)

    if os.access( os.path.join(dirnamein, "offsetbeams.fits"),
                  os.F_OK):
        PlotSimDrizzleBeams( obsdsfname,
                             os.path.join(dirnamein, "offsetbeams.fits"),
                             os.path.join(dirnamein, odir),
                             prefix="offsetbeams",
                             bbox=bbox,
                             fwhm=fwhm,
                             extent=extent,
                             npix=npix,
                             oversample=oversample,
                             ncont=ncont,
                             hardcopy=hardcopy,
                             decorate=decorate)

        PlotAperture( os.path.join(dirnamein, "aperture-offset.fits"),
                      os.path.join(dirnamein, odir),
                      oversample=oversample,
                      prefix="offsetaperture",
                      hardcopy=hardcopy)
        
                         

    
def MkFFMap (fnamein,
             npix=128,
             oversample=2.0):

    "Create the far field map with correct coordinate system"

    
    wavel= oofreduce.GetObsWaveL(fnamein)
    ap =oofreduce.MkSampleAp(fnamein)
    m=pyplot.Map(npix,npix)
    
    pyoof.SetFarFCS( ap.getphase() ,
                     wavel,
                     m);
    return m

    
    

def PlotDSFile( fnamein,
                dirout,
                prefix="beam",
                npix=128,
                oversample=2.0,
                fwhm=2.0,
                extent=4.0,
                bbox=None,
                ncont=None,
                hardcopy=False,
                decorate=True
               ):
    "Plot beams contained in a dataseries file"

    fin=pyfits.open(fnamein)

    m= MkFFMap( fnamein, npix=npix, oversample=oversample)

    #Create the output directory if necessary
    if not os.path.exists(dirout):
        os.makedirs(dirout)

    if hardcopy : end=".eps/CPS"
    else:         end=".png/PNG"        

    for i in range(1,len(fin)):
        ds1=pyplot.LoadFITSDS(fnamein,i+1)

        pyplot.SimpleDrizzle( ds1, m, fwhm , extent)    
        implot.plotmap( m,
                        fout=os.path.join(dirout,
                                          prefix + "-%i%s" % (i, end) ),
                        colmap="heat",
                        bbox=bbox,
                        contours=ncont and implot.MkChopContours(m, nlevels=ncont),
                        plotbox=decorate,
                        plotwedge=decorate)
                                          

def PlotSimDrizzleBeams(obsfilename, beamfilename,
                        dirout,
                        prefix="simdrizbeam",
                        fwhm=1.0, extent=2.0,
                        oversample=2.0,
                        npix=128,
                        bbox=None,
                        ncont=None,
                        hardcopy=False,
                        decorate=True):

    "Create a simulated ds from model beams and then drizzle"

    ds = oofreduce.SimBeamDS(obsfilename, beamfilename)

    if hardcopy : end=".eps/CPS"
    else:         end=".png/PNG"

    for i in range(len(ds)):
        skym=MkFFMap(obsfilename, npix=npix, oversample=oversample)
        pyplot.SimpleDrizzle( ds[i], skym, fwhm , extent)
        implot.plotmap(skym,
                       fout=os.path.join(dirout,
                                         prefix + "-%i%s" % (i, end) ),
                       colmap="heat",
                       bbox=bbox,
                       contours=ncont and implot.MkChopContours(skym, nlevels=ncont),
                       plotbox=decorate,
                       plotwedge=decorate
                       )

def PlotAperture(apfname,
                 dirout,
                 prefix="aperture",
                 oversample=2.0,
                 hardcopy=False):

    "Plot aperture phase and amplitude"

    phasemap=pyplot.FitsMapLoad(apfname,2)
    ampmap  =pyplot.FitsMapLoad(apfname,1)    

    bbox = implot.GetMapBBox(phasemap)
    bbox = [ x/oversample *1.05 for x in bbox]

    if hardcopy:
        end=".eps/PS"
        contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2]
        colmap=None
    else:
        end=".png/PNG"
        contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2]
        colmap="heat"

    implot.plotmap( phasemap,
                    fout=os.path.join(dirout,
                                      prefix+"-phase"+end),
                    bbox=bbox,
                    colmap=colmap,
                    contours=contours,
                    contcolour=0,
                    title=apfname)

    implot.plotmap( ampmap,
                    fout=os.path.join(dirout,
                                      prefix+"-amplitude"+end),
                    bbox=bbox,
                    colmap=colmap   )


def MkApFile(fnamein,
             npix=256,
             telgeo=pyoof.GBTGeo()):

    "Make the aperture phase, illumination pair from a file"

    mphase = pyplot.Map(npix,npix)
    pyplot.MkApCS(mphase, telgeo.DishEffRadius() * 1.05)

    zm = pyoof.RZernModel ( 5 , mphase , telgeo )

    md=pybnmin1.ModelDesc(zm.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    for zn in ["z1" ,"z2"  ] :
        md.getbyname(zn).setp(0)

    zm.Calc(mphase)

    mamp = pyplot.Map(npix,npix)
    pyplot.MkApCS(mamp, telgeo.DishEffRadius() * 1.05)

    im = pyoof.GaussAmpMod ( telgeo , mamp  )

    md=pybnmin1.ModelDesc(im.downcast())
    bnmin1io.FLoad( md, fnamein, silent=True)

    im.Calc(mamp)

    return mphase, mamp

    
    

def PlotZernFile( fnamein,
                  fnameout,
                  npix=256,
                  telgeo=pyoof.GBTGeo(),
                  phaserange=None):

    #Should convert this to use MkApFile
    m = pyplot.Map(npix,npix)
    pyplot.MkApCS(m, telgeo.DishEffRadius() * 1.05)

    zm = pyoof.RZernModel ( 5 , m , telgeo )

    md=pybnmin1.ModelDesc(zm.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    for zn in ["z1" ,"z2"  ] :
        md.getbyname(zn).setp(0)

    zm.Calc(m)

    implot.plotmap( m,
                    fnameout,
                    colmap="heat",
                    contours=[-2,-1.5,-1,-0.5,0,0.5,1,1.5,2],
                    valrange=phaserange)
    return m

    
def PlotIllumFile( fnamein,
                   fnameout,
                   npix=256,
                   telgeo=pyoof.GBTGeo()):

    "Plot illumination from a paremeter file"

    #Should convert this to use MkApFile
    m = pyplot.Map(npix,npix)
    pyplot.MkApCS(m, telgeo.DishEffRadius() * 1.05)

    im = pyoof.GaussAmpMod ( telgeo , m  )

    md=pybnmin1.ModelDesc(im.downcast())

    bnmin1io.FLoad( md, fnamein, silent=True)

    im.Calc(m)

    implot.plotmap( m,
                    fnameout,
                    colmap="heat"                  )

    return m

    

    
                  
    


        

