# Bojan Nikolic
# May 2007
#
# Tests of the Fresenel code

import sys
sys.path.extend(["/import/appcs/bn204/p/bnprog-devel-main/"+x for x in ["bin", "lib"] ])

import pyplot
import pyoof
import implot

import numarray
from matplotlib import pylab

if 0:
    m = pyplot.Map(128,128)
    x=pyplot.dFresnelDir( m, 64, 64, 100)

tel=pyoof.TelSwitch("ALMA")

mamp=pyoof.MkApMap(tel, 128, 2.0)
ilmod=pyoof.GaussAmpMod( tel, mamp)
ilmod.SetSigma(0.3)
ilmod.Calc(mamp)
m3=pyplot.Map(mamp)
implot.plotmap(m3)

mphase=pyoof.MkApMap(tel, 128, 8.0)
ms    =pyoof.MkApMap(tel, 128, 8.0)

fftf=pyplot.FFTFact( m3.nx , m3.ny  , pyplot.FFTFact.forward , pyplot.FFTFact.center)


def P2norm(b1, b2):

    [ pylab.plot( abs(x)**2 / (abs(x)**2).max()) for x in [b1,b2] ]
    pylab.show()
    

def PFren( R):
    x3=numarray.array( [ pyplot.dFresnelDir( m3, i, 64, 1e10) for i in range(0,128) ])
    x4=numarray.array( [ pyplot.dFresnelDir( m3, i, 64, R ) for i in range(0,128) ])

    P2norm(x3,x4)

    
