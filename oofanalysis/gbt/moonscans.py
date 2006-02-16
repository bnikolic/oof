# Bojan Nikolic
# $Id: moonscans.py,v 1.3 2006/02/16 19:52:51 bnikolic Exp $
#
# Analaze moon scans

import math

import pyfits

import numarray
from matplotlib import pylab

import pybnlib
import pyplot
import pyoof
import implot


sfile= "cdata/TPTCSOOF_050324/s75-l.fits"

def PlotF(fname):

    din=pyfits.open(fname)[1].data

    pylab.plot( din.field("dx") * 180 * 60 / math.pi,
                din.field("fnu"))
    pylab.show()

def MkMoon(m):

    # moon radius 15 arcmin
    mradius=15 * math.pi / 180 / 60

    moonfn  =  pybnlib.TopHatDD()
    moonfn  =  mradius
    pyplot.WorldSet( m , moonfn)    

def GenBeam( pixrms,
             fnameout,             
             npix=1024,
             corrscale=4,
             postmult=1
             ):

    oversample=2
    # Note need 2 here for critical sampling!
    tel=pyoof.TelSwitch("GBT")

    mphase=pyoof.MkApMap(tel,
                         npix,
                         oversample)

    mtemp  = pyplot.Map( npix / corrscale,
                         npix / corrscale)

    
    pyplot.NormDist( mtemp,
                     pixrms)

    pyplot.FitsWrite(mtemp, "!temp/temp.fits")
    
    mphase2=pyplot.IntZoom ( mtemp, corrscale)
    mphase2.mult(postmult)
    
    pyplot.FitsWrite(mphase2, "!temp/mphase2.fits")    


    
    #pyplot.NormDist( mphase,
    #                     pixrms)

    mamp=pyoof.MkApMap(tel,
                       npix,
                       oversample)

    mbeam = pyoof.MkApMap(tel,
                          npix,
                          oversample)

    ilmod=pyoof.GaussAmpMod( tel, mamp)
    ilmod.SetSigma(0.3)
    ilmod.Calc(mamp)
    pyplot.FitsWrite(mamp, "!temp/aplitude.fits")

    farf= pyoof.FarF(mamp, 7.3e-3)
    
    farf.Power( mamp, mphase2, mbeam)

    pyplot.FitsWrite(mbeam, fnameout)


def MkSquare (m, s):

    sx = m.nx /2 -s/2
    sy = m.ny /2 -s/2

    for i in range(s):
        for j in range(s):
            m.set(sx+i , sy+j, 1)

            
        
    

def PlotSynthBeam(finlist):

    for fnamein in finlist:

        delt=pyfits.open(fnamein)[0].header["CDELT1"]
        din=pyfits.open(fnamein)[0].data

        nx, ny = din.shape

        fnu = din[ny/2,:]
        dx  = ( numarray.arange(nx, type=numarray.Float64) - nx/2) * delt * 180 * 60 / math.pi

        pylab.plot(dx, numarray.log10(fnu))
        
        
    pylab.show()

    

