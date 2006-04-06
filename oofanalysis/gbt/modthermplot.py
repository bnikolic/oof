# Bojan Nikolic
# $Id: modthermplot.py,v 1.1 2006/04/06 20:02:36 bnikolic Exp $

from  matplotlib import pylab
import pyfits


din = pyfits.open("thermdata/pointastigm.fits")[1].data



def Corr( p1 , p2 ,
          measured=False ):

    if measured:
        din= pyfits.open("thermdata/pointastigm_m.fits")[1].data
    else:
        din = pyfits.open("thermdata/pointastigm.fits")[1].data        

    pylab.clf()
    pylab.scatter( din.field(p1) , din.field(p2))
    for i in range(len(din)):
        pylab.text( din.field(p1)[i] , din.field(p2)[i],
                    "%i" % din.field("scanno")[i])    
    pylab.ylabel(p2 + " (rad) ")
    pylab.xlabel(p1)

    fnameout = "plots/therm%s-vs-%s" % ( p1 , p2 )
    if measured:
        fnameout += "-m"
    pylab.savefig(fnameout+".png")
    pylab.savefig(fnameout+".eps")        


def Corr1( measured=False ):

    if measured:
        din= pyfits.open("thermdata/pointastigm_m.fits")[1].data
    else:
        din = pyfits.open("thermdata/pointastigm.fits")[1].data        

    pylab.clf()
    pylab.scatter( din.field("dynaz") + din.field("lpcaz") , din.field("z3"))
    for i in range(len(din)):
        pylab.text( din.field("dynaz")[i] + din.field("lpcaz")[i] ,
                    din.field("z3")[i],
                    "%i" % din.field("scanno")[i])    
    pylab.ylabel("z3 (rad) ")
    pylab.xlabel("dynaz+lpcaz")
    fnameout = "plots/thermtotaz-vs-z3"
    if measured:
        fnameout += "-m"
    pylab.savefig(fnameout+".png")
    pylab.savefig(fnameout+".eps")        
                  


def Corr2( measured=False  ):

    if measured:
        din= pyfits.open("thermdata/pointastigm_m.fits")[1].data
    else:
        din = pyfits.open("thermdata/pointastigm.fits")[1].data        

    pylab.clf()
    pylab.scatter( din.field("dynel") + din.field("lpcel") , din.field("z5"))
    for i in range(len(din)):
        pylab.text( din.field("dynel")[i] + din.field("lpcel")[i] ,
                    din.field("z5")[i],
                    "%i" % din.field("scanno")[i])    
    
    pylab.ylabel("z5 (rad)")
    pylab.xlabel("dynel+lpcel")

    fnameout = "plots/thermtotel-vs-z5"
    if measured:
        fnameout += "-m"
    pylab.savefig(fnameout+".png")
    pylab.savefig(fnameout+".eps")        

                  


def doplots():

    Corr("lpcel", "z5" , measured=True)
    Corr("dynel", "z5" , measured=True)
    Corr2(measured=True)

    Corr("lpcaz", "z3" , measured=True)
    Corr("dynaz", "z3" , measured=True)
    Corr1(measured=True)

    
    
