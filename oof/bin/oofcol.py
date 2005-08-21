# Bojan Nikolic
# $Id: oofcol.py,v 1.1 2005/08/21 21:46:53 bnikolic Exp $
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

