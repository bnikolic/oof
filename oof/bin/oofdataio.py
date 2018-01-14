# Bojan Nikolic <bojan@bnikolic.co.uk>,   <bn204@mrao.cam.ac.uk>
#
# Utilities for oof data input / output
#

import os

import pyfits
import numpy



def OOFColumns(nrows):

    "Create an empty OOF table"
    
    coldefs = [
        pyfits.Column ( "DX",   "E",   "radians",
                        array=numpy.zeros(nrows)   ),
        pyfits.Column ( "DY",   "E",   "radians",
                        array=numpy.zeros(nrows) ),
        pyfits.Column ( "FNu",   "E",   "Jy",
                        array=numpy.zeros(nrows) ),
        pyfits.Column ( "UFNu",   "E",   "Jy",
                        array=numpy.ones(nrows) ),
        pyfits.Column ( "Time",   "E",   "d",
                        array=numpy.zeros(nrows) )
        ]

    nh = pyfits.new_table( coldefs )
    return nh

def DataSeriesToOOFTable(ds):

    "Convert a dataseries to FITS based oof table"

    tabout=OOFColumns(ds.length())
    d = tabout.data
    
    for i in range(ds.length()):
        d.field("DX")[i] =   ds.getp(i).dX
        d.field("DY")[i] =   ds.getp(i).dY
        d.field("FNu")[i] =  ds.getp(i).fnu
        if 0:
            d.field("UFNu")[i] =  ds.getp(i).ufnu

    return tabout

