# Bojan Nikolic
# $Id: modelwint01.py,v 1.11 2005/12/28 16:53:32 bnikolic Exp $
#
# Make the surface model for winter

import os
from itertools import izip
import math
import pickle

import pyfits
from  matplotlib import pylab
import numarray

from sfcmodels import *

import oofcol
import oofplot
import ooffitconv
import bnmin1io

import pyxplot
import pyplot


#Candidates for excission:
#
# 0911/s37 0911/s45 0911/s77 oofout0911/s29 oofout0912/s155


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

def printelevs():

    res =  []
    for scandir , obsds in izip(allscans , obsscans) :
        el=pyfits.open(obsds)[0].header["meanel"]
        res.append(  ( el, scandir ))
    res.sort()

    for x,y in res:
        print x,y

def OffsetEfficiency(dirin):

    "calculate efficiency loss from offset beam and perfect beams"

    perfbeam  = pyfits.open( os.path.join(dirin, "perfectbeams.fits"))[0].data.max()
    offbeam   = pyfits.open( os.path.join(dirin, "offsetbeams.fits"))[0].data.max()

    return offbeam/ perfbeam
    
def PrintEfficiencies():

    "Print predicted loss of efficiency due to total deformations"

    res =  []
    for scandir , obsds in izip(allscans , obsscans) :
        el=pyfits.open(obsds)[0].header["meanel"]
        
        res.append(  ( el,
                       OffsetEfficiency( scandir) ,
                       scandir)
                     )
    res.sort()

    for x,y,z in res:
        print x,y,z

    pyxplot.scatter( res,
                     "plots/offseteff.eps",
                     width=pyxplot.THESIS,
                     xax=pyxplot.axis(r"$\theta\,$(deg)", xmin=0 , xmax=90),
                     yax=pyxplot.axis(r"$\epsilon_{\rm LSS}$"),
                     symbsize=0.05,
                     addp=lambda g : g.plot(pyxplot.graph.data.function(
        "y=exp(-1.0 * ((x-52)/52)**2)")))
    

def ElHist():

    "Compute histogram of measured elevations"

    res =  []
    for scandir , obsds in izip(allscans , obsscans) :
        el=pyfits.open(obsds)[0].header["meanel"]
        
        res.append(el)

    res.sort()

    pyxplot.histogram( [ ( res , "" ) ],
                       "plots/el-hist.eps",
                       width=pyxplot.THESIS ,
                       key=None ,
                       nbins=9,
                       xax=pyxplot.axis(r"$\theta\,$(deg)", xmin=0 , xmax=90)
                       )


    
    

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

def MkModel(outputmod=True,
            printmod =True):

    resd = {}
    for i in range(3,21):
        pname="z%i" % i 
        res= fitfn(pname)
        resd[pname] = MkHFn(  res[0] , res[1],res[2] )
        if printmod:
            n,l=ooffitconv.OOFktoOOFnl(i)
            print r"%i & %i & %2.1f & %2.1f & %2.1f & %3.2f & %3.2f \\" % (n , l ,
                                                           res[0] ,
                                                           res[1],
                                                           res[2],
                                                           ParRMS(pname),
                                                           ParRMS(pname, resd[pname]))


    fsample = os.path.join(allscans[0], "offsetpars.fits" )

    f=pyfits.open(fsample)

    if outputmod:
        for el in [ 10 + i*5 for i in range(14)]:
            for row in f[1].data:
                key=row.field("parname")
                if  key in resd:
                    row.setfield("parvalue", resd[key](el))
            iofits4.Write(f, "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                          overwrite=True)
            oofplot.PlotZernFile( "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                                  "models/Wint2005V1/surfacepars-el%i.png/PNG" % el )

            oofplot.PlotZernFile( "models/Wint2005V1/surfacepars-el%i.fits" % el ,
                                  "models/Wint2005V1/surfacepars-el%i.eps/CPS" % el )

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
    #print res

    pylab.clf()
    pylab.plot( elevs, vals)
    pylab.plot( elevs, HookModel( elevs, res[0][0] , res[0][1],res[0][2] ) )
    pylab.savefig("model/%s.png" % pname)

    pickle.dump( [ elevs,
                   vals,
                   HookModel( elevs, res[0][0] , res[0][1],res[0][2] )],
                 open( "model/%s.pickle" % pname , "w") )

    return res[0]

def ParRMS( pname , model=None ):

    pdata=getpardata(pname)
    pdata.sort()

    elevs= numarray.array( [ x[0] for x in pdata ] )
    vals = numarray.array( [ x[1] for x in pdata ] )

    if model :
        mvals = numarray.array( [ model(x) for x in elevs] )
    else:
        mvals = numarray.zeros( len (elevs) )

    return (((vals-mvals)**2).mean())**0.5

    

    
def PlotClosure():

    "Illustrate the closure of the technique"

    measuredir= "oofout0911/s6-l-db-000/z5"
    corrdir   = "oofout0911/s29-l-db-000/z5"

    phase1 = oofplot.PlotZernFile( os.path.join(measuredir ,
                                       "fitpars.fits"),
                                   "plots/measuresfc.eps/CPS")
    i1    = oofplot.PlotIllumFile( os.path.join(measuredir ,
                                                "fitpars.fits"),
                                   "plots/measureamo.eps.eps/CPS")

    print "Unweighted RMS  " , pyplot.MapRMS(phase1)
    print "RMS measured : " , pyplot.MapRMS(phase1, i1)

    phase2= oofplot.PlotZernFile( os.path.join(corrdir ,
                                              "fitpars.fits"),
                                 "plots/corrmeasuresfc.eps/CPS")
    i2    = oofplot.PlotIllumFile( os.path.join(corrdir ,
                                                "fitpars.fits"),
                                   "plots/corrmeasureamp.eps/CPS")
    print "RMS corrected : " , pyplot.MapRMS(phase2, i2)
    
    
    
def PlotSfcs():

    def plot ( sdate, sno ):

        zfin = "oofout%s/s%i-l-db-000/z5/offsetpars.fits" % ( sdate, sno )
        oofplot.PlotZernFile( zfin,
                              "plots/sfc%s-%i.eps/CPS" % (sdate, sno) )
        oofplot.PlotZernFile( zfin,
                              "plots/sfc%s-%i.png/PNG" % (sdate, sno) )

        #oofplot.PlotIllumFile ( zfin,
        #"plots/sfc%s-%i-amp.eps/CPS" % (sdate, sno) )
        


    if 0:
        plot( "0411" , 198)
        plot( "0411" , 141)
        plot( "0911" , 101)

        plot( "0912" , 51)
        plot( "0912" , 75)

        plot( "0911" , 6)
        plot( "0912" , 131)    

    if 0:
        plot( "0411" , 114)

    if 0:
        #illustrate each decade of elevation:
        plot( "0912" , 27)
        plot( "0912" , 91)

        plot( "0912" , 75)
        plot( "0912" , 51)

        plot( "0911" , 93)
        plot( "0411" , 156)

        plot( "0911" , 69)
        plot( "0912" , 115)

        plot( "0911" , 6)
        plot( "0912" , 131)




def PlotObs():

    oofplot.PlotDir( "oofout0411/s114-l-db-000/z5",
                     bbox=[-0.6e-3, 0.4e-3, -0.5e-3, 0.5e-3],
                     npix=512,
                     fwhm=4, extent=10,
                     ncont=5,
                     hardcopy=True)


def Report():

    "Print a report on the observations and models"

    scanlist=  [("050911", x ) for x in sl0911 ]+ [("050912", x ) for x in sl0912 ]+     [("050411", x ) for x in sl0411 ]

    for sname, scandir, obsds in izip ( scanlist, allscans, obsscans):
        el=pyfits.open(obsds)[0].header["meanel"]
        print r"%s & %i & %i \\" % ( sname[0] , sname[1],el)
                                     

def PolyPrint():

    for i in range(3,21):
        n,l=ooffitconv.OOFktoOOFnl(i)
        print "($n=%i$, $l=%i$)," % ( n ,l)


def Ruze ( rms , freq  ):

    return math.exp(-1.0 * (4* math.pi * rms / (3e8/freq))**2)

