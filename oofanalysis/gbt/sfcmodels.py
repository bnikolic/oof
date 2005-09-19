# Bojan Nikolic
# $Id: sfcmodels.py,v 1.2 2005/09/19 15:16:52 bnikolic Exp $
#
# General support for producing surface models

import os
from itertools import izip
import math

import pyfits
import numarray

from scipy.optimize import leastsq

import iofits4

def MeanModel ( flist , fnameout ):

    f0 = pyfits.open(flist[0] )

    pardict = {}

    for parname, parvalue in izip(f0[1].data.field("ParName"),
                                  f0[1].data.field("ParValue")):
        pardict[parname] =  [ parvalue ]


    for fnamein in flist[1:]:
        fcur=pyfits.open(fnamein )
        for parname, parvalue in izip(fcur[1].data.field("ParName"),
                                      fcur[1].data.field("ParValue")):
            if parname in pardict:
                pardict[parname] =  pardict[parname] + [ parvalue ]

    for row in f0[1].data:
        row.setfield( "ParValue" ,
                      (numarray.array(pardict[ row.field("parname")])).mean() )
    
    iofits4.Write(f0, fnameout , overwrite =True )


def HookModel( elevs , c , fsin , fcos ):

    return c+ fsin  * numarray.sin(elevs * math.pi / 180 ) + fcos  * numarray.cos(elevs * math.pi / 180 )

def HookModelFit(x0 , elevs, vals ):

    c , fsin , fcos = x0
    return vals - HookModel( elevs, c , fsin , fcos)


    
    
