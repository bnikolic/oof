# Bojan Nikolic <bojan@bnikolic.co.uk>
#
# January 2008
#
# Processing/analysis of mustang data

import os
import setup

import pyfits
import numarray

import iofits4
import oofreduce
import oofplot


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

def PlotPixTimeSer(fnamein,
                   hduno,
                   pixno):

    f=pyfits.open(fnamein)
    mask= ( f[hduno].data.field("PixID") == pixno)
    pylab.plot( f[hduno].data.field("time")[mask],
                f[hduno].data.field("fnu")[mask])
    

def RedTPAR18():

    dirin= "/home/bnikolic/data/gbt-oof/mustang/TPAR18/"
    obslist = [ "0854+2006tpar18s56s58.fits",
                "0854+2006tpar18s59s61.fits",
                "0854+2006tpar18s64s66.fits" ]

    for f in obslist:
        fnamein=os.path.join(dirin, f)
        CorrectDZ(fnamein)
        fs=fnamein[:-5] + "_s.fits"
        RemoveStartEnd( fnamein ,
                        fs)

        oofreduce.Red(fs)
        
        
        
