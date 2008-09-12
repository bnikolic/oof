# Bojan Nikolic <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Illustrate drizzling observed data onto 2d map and saving to FITS
# file

import os
import pyfits

# This is a file which adjusts my PYTHONPATH on-line to allow testing
# multiple builds, you shouldn't need this
import setup

import pyplot
import pybnfits
import oofreduce
import oofplot

def getNHDU(fnamein):
    """Return the number of HDU in FITS file"""
    return len(pyfits.open(fnamein))

def saveObsBeams(fnamein,
                 fnameoutpref,
                 npix=128,
                 oversample=2.0,
                 fwhm=2.0,
                 extent=4.0,
                 ):
    """
    Save Observed beams to a FITS file

    :param fnamein: filename with the observation

    :param fnameoutpref: The prefix of the output filename. The beams
    will be written with "-1.fits", "-2.fits" etc added to the
    filename. (Not exactly consistent with simulated beams
    unfortunately). If exclamation mark is the first character, then
    file gets overwritten. If file exists and is not to be
    overwritten, then the program exists. 

    :param fwhm: FWHM of kernel used to iterpolate observed beams
    onto positions of the telescope
    
    :param extent: Extent of the kernel used to iterpolate observed
    beams onto positions of the telescope

    Example usage:

    >>> saveObsBeams("/home/bnikolic/data/gbt-oof/q-band/old/s114-l-db.fits", 
                     "!temp/s114-test-obs")

    """
    nhdu=getNHDU(fnamein)
    m=oofplot.MkFFMap(fnamein,
                      npix=npix,
                      oversample=oversample)
    for i in range(1,nhdu):
        #Note the 1-based indexing of HDUs required by cfitsio...
        ds1=pyplot.LoadFITSDS(fnamein,
                              i+1)
        pyplot.SimpleDrizzle(ds1,
                             m, 
                             fwhm, 
                             extent)                 
        pyplot.FitsWrite(m,
                         fnameoutpref+"-%i.fits"%i)

