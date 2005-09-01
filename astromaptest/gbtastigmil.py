# Bojan Nikolic
# $Id: gbtastigmil.py,v 1.1 2005/09/01 19:21:46 bnikolic Exp $
#
# Illustrate where astigmatism comes in from at the gbt

import math

import pyplot
import pyoof
import implot
import pybnlib

npix =256


tel1=pyoof.PrimeFocusGeo()
tel1.PrimRadius=1
tel1.PrimF=1

tilt= -0.009
#tilt= 0

def mkfocmove():
    
    m = pyplot.Map(npix, npix)
    pyplot.MkApCS(m, 1.2)

    mask = pyoof.Clone(m)
    tel1.DishMask(mask)

    dX = 0.01 * math.cos( 36.7 * math.pi / 180 )
    dY = 0.01 * math.sin( 36.7 * math.pi / 180 )
    tel1.MkFocMove(dX,0,dY,m)
    m.mult( mask)

    return m, mask

m,mask= mkfocmove()

scratch = pyplot.Map(npix, npix)
pyplot.MkApCS(scratch, 1.2)

zfn=pybnlib.ZernPoly(1,1)
pyplot.WorldSet( scratch , zfn)
scratch.mult(tilt)
m.add(scratch)
m.mult( mask)

implot.plotmap(m, colmap="heat", fout="gbtil/wholeap.png/PNG")

th1  =  pybnlib.TopHatDD()
th1.x0 = 0.5
th1.radius=0.5
mask1 = pyoof.Clone(m)
pyplot.WorldSet( mask1 , th1)
m.mult(mask1)

implot.plotmap(m, colmap="heat", fout="gbtil/apX.png/PNG")

tel1.MkFocMove(0.01,0,0,m)
m.add(scratch)
m.mult( mask)

th2  =  pybnlib.TopHatDD()
th2.y0 = 0.5
th2.radius=0.5
mask2 = pyoof.Clone(m)
pyplot.WorldSet( mask2 , th2)

m.mult(mask2)
implot.plotmap(m, colmap="heat", fout="gbtil/apY.png/PNG")











