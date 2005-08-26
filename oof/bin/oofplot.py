# Bojan Nikolic
# $Id: oofplot.py,v 1.4 2005/08/26 21:08:06 bnikolic Exp $
#
# Various utilities for plotting OOF data

import os

import pyfits

import implot
import pyplot
import pyoof

import oofreduce
import oofcol

def PlotDir(dirnamein, bbox=None):

    "Make all the relevant plots"

    obsdsfname=  oofcol.getpar(dirnamein,  "fitinfo.fits", "obsfilename")
    npix= int(oofcol.getpar(dirnamein,  "fitinfo.fits", "npix") )
    oversample= float( oofcol.getpar(dirnamein,  "fitinfo.fits", "oversample") )
    fwhm=float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_fwhm") )
    extent=float(oofcol.getpar(dirnamein,  "fitinfo.fits", "ds_extent") )

    PlotDSFile( obsdsfname,
                os.path.join(dirnamein, "plots"),
                prefix="obsbeam",
                oversample= oversample,
                npix=npix,
                fwhm=fwhm,
                extent=extent,
                bbox=bbox)

    PlotSimDrizzleBeams( obsdsfname,
                         os.path.join(dirnamein, "fitbeams.fits"),
                         os.path.join(dirnamein, "plots"),
                         prefix="bestfitbeams",
                         bbox=bbox,
                         fwhm=fwhm,
                         extent=extent)
                         

    
                
    

def PlotDSFile( fnamein,
                dirout,
                prefix="beam",
                npix=128,
                oversample=2.0,
                fwhm=2.0,
                extent=4.0,
                bbox=None
               ):
    "Plot beams contained in a dataseries file"

    fin=pyfits.open(fnamein)


    # Make a map with the correct coordinate system
    wavel= oofreduce.GetObsWaveL(fnamein)
    ap =oofreduce.MkSampleAp(fnamein)
    m=pyplot.Map(npix,npix)
    
    pyoof.SetFarFCS( ap.getphase() ,
                     wavel,
                     m);

    #Create the output directory if necessary
    if not os.path.exists(dirout):
        os.makedirs(dirout)    

    for i in range(1,len(fin)):
        ds1=pyplot.LoadFITSDS(fnamein,i+1)
        pyplot.SimpleDrizzle( ds1, m, fwhm , extent)    

        implot.plotmap( m,
                        fout=os.path.join(dirout,
                                          prefix + "-%i.png/PNG" % i ),
                        colmap="heat",
                        bbox=bbox)
                                          

def PlotSimDrizzleBeams(obsfilename, beamfilename,
                        dirout,
                        prefix="simdrizbeam",
                        fwhm=1.0, extent=2.0,
                        bbox=None):

    ds = oofreduce.SimBeamDS(obsfilename, beamfilename)
    print ds

    for i in range(len(ds)):
        skym=pyplot.FitsMapLoad(beamfilename, i+1)
        pyplot.SimpleDrizzle( ds[i], skym, fwhm , extent)
        print i
        implot.plotmap(skym,
                       fout=os.path.join(dirout,
                                         prefix + "-%i.png/PNG" % i ),
                       colmap="heat",
                       bbox=bbox)



        

