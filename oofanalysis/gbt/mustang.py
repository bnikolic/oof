# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# Initial version January 2008
#
# Processing/analysis of mustang data

import os
import tarfile

import setup


import pyfits
import numarray

import iofits4
import oofreduce
import oofplot

import pyplot
import implot


def CorrectDZ(fnamein):

    "Correct fits files which have dz in mm instead of m"

    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:
        dz=h.header["dz"]
        print dz
        if abs(dz) < 1.0 :
            print "DZ already less than 1.0, presumably in meters"
        else:
            h.header.update("DZ", dz * 1e-3,
                            "Telescope defocus (m) ")
        res.append(h)
            
    iofits4.Write(res,
                  fnamein,
                  overwrite=1)
    

def RemoveStartEnd(fnamein,
                   fnameout,
                   cut=5.0):

    "Remove the starts and the ends of the scans"

    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:

        time=h.data.field("time")
        mt  = max(time)

        mask = numarray.logical_and( time > cut,
                                     time < ( max(time) - cut))
        print sum(mask)

        print len(h.data)
        h.data = pyfits.FITS_rec(h.data[mask])
        print len(h.data)        
        res.append(h)
            
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)

def SelectCR( din,
              colno,
              rowno):

    """
    Select a single pixel by column and row numbers
    """

    return numarray.logical_and( din.field("col") == colno,
                                 din.field("row") == rowno)

def SinglePixelFile(fnamein,
                    fnameout,
                    colno,
                    rowno):


    fin=pyfits.open(fnamein)

    res=[ fin[0]]
    for h in fin[1:]:

        mask=SelectCR(h.data, colno, rowno)

        h.data = pyfits.FITS_rec(h.data[mask])
        res.append(h)
            
    iofits4.Write(res,
                  fnameout,
                  overwrite=1)

def PlotPixTimeSer(fnamein,
                   hduno,
                   pixno):

    f=pyfits.open(fnamein)
    mask= ( f[hduno].data.field("PixID") == pixno)
    pylab.plot( f[hduno].data.field("time")[mask],
                f[hduno].data.field("fnu")[mask])
    


tpar18list=  [ "0854+2006tpar18s56s58.fits",
               "0854+2006tpar18s59s61.fits",
               "0854+2006tpar18s64s66.fits" ]

def RedTPAR18():

    dirin= "/home/bnikolic/data/gbt-oof/mustang/TPAR18/"
    obslist = tpar18list

    for f in obslist:
        fnamein=os.path.join(dirin, f)
        CorrectDZ(fnamein)
        fs=fnamein[:-5] + "_s.fits"
        RemoveStartEnd( fnamein ,
                        fs)

        oofreduce.Red(fs)
        
        
def PlotAndPack():

    tf=tarfile.open("oofout/tpar18analysis.tar.bz2" , "w:bz2")

    for f in tpar18list:
        fs = os.path.join("oofout", f[:-5] + "_s-000"  , "z5")
        oofplot.PlotDir(fs, bbox=[ -6e-4 * x for x in [-1 ,1,-1,1] ])
        tf.add( fs )

def PlotObitMUSTANG(sno):

    fnamein="/home/bn204/d/data/oof/gbt/mustang/obit/OOF/0854+2006.%i.CalImage.fits" % sno

    m=pyplot.FitsMapLoad(fnamein ,1)
    pyplot.ReplaceInfNaN(m, 0)

    implot.plotmap(m, colmap="heat")
    
    
    
