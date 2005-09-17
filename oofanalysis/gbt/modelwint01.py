# Bojan Nikolic
# $Id: modelwint01.py,v 1.1 2005/09/17 19:34:43 bnikolic Exp $
#
#

import os
from itertools import izip

import pyfits
from  matplotlib import pylab

import oofcol
import bnmin1io

sl0911 = [6 , 14 , 29,  37 , 45, 53 ,69, 77, 85, 93, 101 ]

#sl0912 = [ 11, 19 , 27 , 35, 43, 51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
#           147, 155]

sl0912 = [ 11, 19 , 27 , 35,  51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
           147, 155]

allscans = [ "oofout0911/s%i-l-db-000/z5" %i for i in sl0911] + [ "oofout0912/s%i-l-db-000/z5" %i for i in sl0912]

dd12="/home/bnikolic/data/gbtoof/ver001/0912"
dd11="/home/bnikolic/data/gbtoof/ver001/0911"

obsscans= [ os.path.join( dd11, "s%i-l-db.fits" %sno ) for sno in sl0911 ] +[ os.path.join( dd12, "s%i-l-db.fits" %sno ) for sno in sl0912 ]

# Comments on individual scans:
#
# Scan #0912//43 give crazy results... observed maps look strange
# investigate weather non even timing error is the cause? - not the non-even sampling

def plotparvselev(pname):

    pdata = []

    for scandir , obsds in izip(allscans , obsscans) :
        el=pyfits.open(obsds)[0].header["meanel"]
        par= bnmin1io.FGetPar(os.path.join(scandir, "fitpars.fits" ) , pname)
        
        pdata.append( ( el,par, obsds ) )

    pdata.sort()
    print pdata

    pylab.plot( [x[0] for x in pdata ] , [x[1] for x in pdata ])
    

    
    


