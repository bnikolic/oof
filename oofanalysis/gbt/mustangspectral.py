"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

Spectral analysis of MUSTANG data

"""

import pyfits
import numpy

import pylab

def fnuspec(fnamein,
            nf=256):
    x=[]
    for i in range(1,4):
        d=pyfits.open(fnamein)[1].data
        x.extend(list(d.field("fnu")))
    x=numpy.array(x)
    x=x/numpy.max(x)
    pylab.psd(x,
              NFFT=nf)
    
def a1():
    sets=["/home/bnikolic/data/gbt-oof/mustang3/tpar18s56s58-02jul080854+2006.fits",
          "/home/bnikolic/data/gbt-oof/mustang2/tpar18s56s58-apr080854+2006.fits",
          "/home/bnikolic/data/gbt-oof/mustang4/tpar18s56s58-19nov08-p12-noqd0854+2006.fits"]
    pylab.clf()
    for x in sets:
        fnuspec(x)
        pylab.savefig("o/PSDcomparison.png")
