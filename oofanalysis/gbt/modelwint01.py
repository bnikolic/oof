# Bojan Nikolic
# $Id: modelwint01.py,v 1.2 2005/09/19 15:16:52 bnikolic Exp $
#
# Make the surface model for winter

import os
from itertools import izip
import math

import pyfits
from  matplotlib import pylab
import numarray

from sfcmodels import *

import oofcol
import oofplot
import ooffitconv
import bnmin1io




sl0911 = [6 , 14 , 29,  37 , 45, 53 ,69, 77, 85, 93, 101 ]

#sl0912 = [ 11, 19 , 27 , 35, 43, 51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
#           147, 155]

sl0912 = [ 19 , 27 , 35,  51, 59, 67, 75,  83,  91 ,  99 , 107 , 115,  123,  131 ,  139,
           147, 155]

sl0411 = [114, 141, 156, 183, 198, 225, 240, 348, 375]



allscans = [ "oofout0911/s%i-l-db-000/z5" %i for i in sl0911] + [ "oofout0912/s%i-l-db-000/z5" %i for i in sl0912] + [ "oofout0411/s%i-l-db-000/z5" %i for i in sl0411]

dd12="/home/bnikolic/data/gbtoof/ver001/0912"
dd11="/home/bnikolic/data/gbtoof/ver001/0911"
dd0411="/home/bnikolic/data/gbtoof/ver001/0411"

obsscans= [ os.path.join( dd11, "s%i-l-db.fits" %sno ) for sno in sl0911 ] +[ os.path.join( dd12, "s%i-l-db.fits" %sno ) for sno in sl0912 ] + [ os.path.join( dd0411, "s%i-l-db.fits" %sno ) for sno in sl0411 ] 

# Comments on individual scans:
#
# Scan #0912//43 give crazy results... observed maps look strange
# investigate weather non even timing error is the cause? - checked:
# not the non-even sampling

# Scan #0912//11 has pretty low signal to noise - exclude

def getpardata(pname):

    pdata = []
    for scandir , obsds in izip(allscans , obsscans) :
        el=pyfits.open(obsds)[0].header["meanel"]
        par= bnmin1io.FGetPar(os.path.join(scandir, "offsetpars.fits" ) , pname)
        
        pdata.append( ( el,par, obsds ) )

    return pdata
    

def plotparvselev(pname, setup=True):

    pdata=getpardata(pname)

    pdata.sort()
    print pdata

    if setup: pylab.clf()
    pylab.plot( [x[0] for x in pdata ] , [x[1] for x in pdata ])
    if setup: pylab.show()
    

def doffall():
    for i in range(3,21): fitfn("z%i" % i )

def MkHFn(a , b ,c ):

    return lambda e : HookModel( e, a, b, c)

def MkModel():

    resd = {}
    for i in range(3,21):
        pname="z%i" % i 
        res= fitfn(pname)
        resd[pname] = MkHFn(  res[0] , res[1],res[2] )

    fsample = os.path.join(allscans[0], "offsetpars.fits" )

    f=pyfits.open(fsample)

    for el in [ 10 + i*5 for i in range(14)]:
        for row in f[1].data:
            key=row.field("parname")
            if  key in resd:
                row.setfield("parvalue", resd[key](el))
        iofits4.Write(f, "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                      overwrite=True)
        oofplot.PlotZernFile( "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                              "models/Wint2005V1/surfacepars-el%i.png/PNG" % el )

        wavel=0.0069569925090132347

        ooffitconv.MkGBTSfcFile( "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                                 "models/Wint2005V1/gbt/surfacepars-el%i.fits" % el ,
                                 wavel)
            
        
        
    
    
def fitfn( pname ):

    pdata=getpardata(pname)
    pdata.sort()

    elevs= numarray.array( [ x[0] for x in pdata ] )
    vals = numarray.array( [ x[1] for x in pdata ] )

    res=leastsq( HookModelFit ,
                 (0.0 , 0.0 , 0.0 ) ,     (elevs, vals))
    print res

    pylab.clf()
    pylab.plot( elevs, vals)
    pylab.plot( elevs, HookModel( elevs, res[0][0] , res[0][1],res[0][2] ) )
    pylab.savefig("model/%s.png" % pname)

    return res[0]

    
    

    
    



