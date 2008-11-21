"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

Spectral analysis of MUSTANG data

"""

import pyfits

import pylab

def fnuspec(fnamein,
            nf=256):
    x=[]
    for i in range(1,4):
        d=pyfits.open(fnamein)[1].data
        x.extend(list(d.field("fnu")))
    pylab.psd(x,
              NFFT=nf)
    
