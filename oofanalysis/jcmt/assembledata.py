# Bojan Nikolic <bn204@mrao.cam.ac.uk>, <bojan@bnikolic.co.uk>
# August 2007
#
# Convert very old data from JCMT to conforming FITS format

import math

from setup import *

import pyfits
import iofits4

import numarray

def JCMTAsciiToArray(fnamein):

    """
    First two rows: numbers of rows + columns
    """

    dl = [ x for x in open(fnamein) ]

    ncols= int(dl[0])
    nrows= int(dl[1])

    res=numarray.zeros( (ncols, nrows), numarray.Float64)

    for j in range(nrows):
        for i in range(ncols):
            res[i,j]= float( dl[ 2+ i + j * ncols] )

    return res

def JCMTArrayToHDU(ar,
                   pixsize_arcsecs,
                   dz):

    "Convert array to table HDU"

    dx=numarray.zeros( ar.shape, numarray.Float64)
    dy=numarray.zeros( ar.shape, numarray.Float64)
    
    for j in range(ar.shape[1]):
        dx[:,j]= numarray.arange(-ar.shape[0]/2.0 * pixsize_arcsecs,
                                 ar.shape[0]/2.0 * pixsize_arcsecs, pixsize_arcsecs)
    for i in range(ar.shape[0]):
        dy[i,:]= numarray.arange(-ar.shape[1]/2.0 * pixsize_arcsecs,
                                 ar.shape[1]/2.0 * pixsize_arcsecs, pixsize_arcsecs)

    # Convert to radians
    dx *= math.pi / 180
    dy *= math.pi / 180

    coldefs = [
        pyfits.Column ( "DX",   "E",   "radians",
                        array=dx.flat ),
        pyfits.Column ( "DY",   "E",   "radians",
                        array=dy.flat),
        pyfits.Column ( "fnu",   "E",   "Jy",
                        array=ar.flat ),
        pyfits.Column ( "UFNU",   "E",   "Jy",
                        array=numarray.ones(len(dx.flat))),
        pyfits.Column ( "TIME",   "E",   "d",
                        array=numarray.arange(len(dx.flat)))
        ]

    nh = pyfits.new_table( coldefs )
    nh.header.update("dz", dz )    

    return nh


def JCMTRecAPrimary():

    "Primary HDU for JCMT + Receiver A"

    res=pyfits.PrimaryHDU()

    res.header.update("freq" ,   3e8/850e-6 )
    res.header.update("chopthr", 160)     #need to fix this            
        
    res.header.update("telesc", "JCMT")
    res.header.update("objsize", 0.0)
    res.header.update("obstype", "AZCHOP")
    res.header.update("Recv", "RECA")

    return res
    
def JCMTAssembleRecA(finlist,
                     fnameout):

    "Assemble receiver A data "

    hl = [ JCMTRecAPrimary() ]

    for finname, dz in finlist:
        a=JCMTAsciiToArray(finname)
        hl.append( JCMTArrayToHDU(a, 8.0, dz))

    iofits4.Write( hl ,
                   fnameout ,
                   overwrite=1 ,
                   mkpath=1)
    
def BuildTest():

    d="/home/bnikolic/temp/jcmtdata/jcmt/singlebeam/venusnew/"

    fl= [ ( "Oi84.dat", 0 ),
          ( "Oi85.dat", -0.002 ),
          ( "Oi86.dat", 0.002 ) ]

    fl = [ (os.path.join(d,x), y) for x,y in fl]
    
    JCMTAssembleRecA(fl,
                     os.path.join(d, "venus.fits"))
