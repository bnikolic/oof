# Bojan Nikolic
# $Id: oofcol.py,v 1.4 2006/03/04 16:18:09 bnikolic Exp $
#
# Various routines to help with collating oof data

import os
import re

import pyfits

from itertools import izip

fitre=re.compile(r"^(?P<basename>.*)(\.fits|\.fit|\.FIT|\.FITS)$")

def basename(fname):
    "Remove directory part and .fits/.fit part of a filename"

    m=fitre.match( os.path.basename(fname) )
    if m:
        return m.group("basename")
    else :
        raise "Not a fits file name"

def mkodir( base, prefix , fill =3 ):

    "Make a sequentially numbered output directory"

    i =0
    while ( os.access( os.path.join(base, prefix+ ( "-%0*i" % (fill,i))), os.F_OK) ):
        i+=1

    os.makedirs( os.path.join(base, prefix+ ( "-%0*i" % (fill,i))))
    return os.path.join(base, prefix+ ( "-%0*i" % (fill,i)))


def getpar(dirin, parfile , parname, extno=1,
           parcol="parameter",
           valcol="value"):

    "Return the requested parameter from a fits table"

    fnamein=os.path.join(dirin, parfile)

    dat=pyfits.open(fnamein)[extno].data

    sres = dat.field(parcol).search(parname)
    if len( sres[0] ) == 0:
        raise "Parameter %s not found" % parname

    parindex = sres[0][0]

    return dat.field(valcol)[parindex]

def direlev(dirin):

    "Get mean elevation of observations from an oof output directory"

    """
    Currently mean elevation is not coppied accros so the original
    observations file must still exist
    """

    obsdsfname=  getpar(dirin,  "fitinfo.fits", "obsfilename")

    return float( pyfits.open(obsdsfname)[0].header["meanel"])

                  
    
    
