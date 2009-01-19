"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

Takeup some of the aperutre phase error by adjusting the subreflector
focus position
"""
import re
import numpy
import pyfits

import ooffitconv

__version__ = "0.5"

# This is the output of the gbtdefoczerns.py script
gbtdefocus= {'z20': -9.5329830732060556e-05, 
             'z18': -9.5328703631562242e-05, 
             'z19': -9.5329081051951102e-05, 
             'z16': 0.00043877660467531789, 
             'z17': 0.0013081595410069302, 
             'z14': -0.0014611841223999024, 
             'z15': -4.3236627549748424e-05, 
             'z12': 0.0021510042923925665, 
             'z13': 0.0029258286313106098, 
             'z10': -2.4316080931909111e-18, 
             'z11': 1.6140014290768439e-18, 
             'z8': -6.3535688539061969e-05, 
             'z9': -6.3535854273657518e-05, 
             'z4': -0.12404699379120403, 
             'z5': -0.011851391922892699, 
             'z6': -0.0015581636239436953, 
             'z7': -0.023563526207155881, 
             'z3': -8.4005579206337868e-19}

def mkVect(dzdict,
           kmax=21):
    """
    Convert dictionary into a vector
    """
    v=[dzdict["z%i"%k] for k in range(3,kmax)]
    return numpy.array(v)

def fitparsVect(fnamein):
    surfacedict=ooffitconv.LoadFITS(fnamein)
    return mkVect(surfacedict)

def GBTTakeup(fnamein,
           fnameout):
    """
    Take up as much of surface error with the GBT subreflector
    movement
    
    :param fnamein: Input file name. The file format should be similar
    to "fitpars.fits" produced by OOF.

    :param fnameout: Output file name. Will be overwritten if already
    exists.
    """
    surfacev=fitparsVect(fnamein)
    dzv=mkVect(gbtdefocus)
    c=numpy.vdot(surfacev,dzv) / numpy.vdot(dzv,dzv)
    surfacedict=ooffitconv.LoadFITS(fnamein)
    zrex=re.compile ("^z(\d)+")
    for k in surfacedict.keys():
        if zrex.match(k):
            if k in gbtdefocus:
                surfacedict[k] -= c*gbtdefocus[k]
    surfacedict["dz"]=c
    ooffitconv.SaveFITS(surfacedict, 
                        fnameout,
                        {"tkdzV" : __version__})
    



