# Bojan Nikolic
# $Id: moonscans.py,v 1.1 2006/02/16 14:55:25 bnikolic Exp $
#
# Analaze moon scans

import pyfits
import numarray
from matplotlib import pylab

import pyplot
import pyoof
import implot


sfile= "cdata/TPTCSOOF_050324/s75-l.fits"

def PlotF(fname):

    din=pyfits.open(fname)[1].data

    pylab.plot( din.field("dx"),
                din.field("fnu"))
    pylab.show()

def GenBeam( pixrms,
             fnameout,             
             npix=512
             ):

    oversample=2
    tel=pyoof.TelSwitch("GBT")

    mphase=pyoof.MkApMap(tel,
                         npix,
                         oversample)
    pyplot.NormDist( mphase,
                     pixrms)
    
    mamp=pyoof.MkApMap(tel,
                       npix,
                       oversample)

    mbeam = pyoof.MkApMap(tel,
                       npix,
                         oversample)

    ilmod=pyoof.GaussAmpMod( tel, mamp)
    ilmod.SetSigma(0.3)
    ilmod.Calc(mamp)

    farf= pyoof.FarF(mamp, 7.3e-6)
    
    farf.Power( mamp, mphase, mbeam)

    pyplot.FitsWrite(mbeam, fnameout)

def PlotSynthBeam(finlist):

    for fnamein in finlist:
        
        din=pyfits.open(fnamein)[0].data

        nx, ny = din.shape

        fnu = din[ny/2,:]

        pylab.plot(numarray.log10(fnu))
        
    pylab.show()

    

