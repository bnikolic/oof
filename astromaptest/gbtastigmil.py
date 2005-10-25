# Bojan Nikolic
# $Id: gbtastigmil.py,v 1.3 2005/10/25 16:40:14 bnikolic Exp $
#
# Illustrate where astigmatism comes in from at the gbt

import math

import pyplot
import pyoof
import implot
import pybnlib

ParentRadius=200

npix =256


tel1=pyoof.PrimeFocusGeo()
tel1.PrimRadius=ParentRadius
tel1.PrimF= ParentRadius * 1

#wholetilt = 0
#wholetilt=-4.5e-3 /200.0
wholetilt= -9e-3 /200.0

#tilt= -0.009
#tilt= 0

def mkfocmove():
    
    m = pyplot.Map(npix, npix)
    pyplot.MkApCS(m, ParentRadius * 1.2)

    mask = pyoof.Clone(m)
    tel1.DishMask(mask)


    #dX = 0.01 * math.cos( 36.7 * math.pi / 180 )
    #dY = 0.01 * math.sin( 36.7 * math.pi / 180 )
    
    dX = 0.01 * math.sin( 36.7 * math.pi / 180 )
    #dY = 0.01 * math.cos( 36.7 * math.pi / 180 )
    dY=0
    
    tel1.MkFocMove(dX,0,dY,m)
    m.mult( mask)

    return m, mask

m,mask= mkfocmove()

scratch = pyplot.Map(npix, npix)
pyplot.MkApCS(scratch, ParentRadius *1.2)

zfn=pybnlib.ZernPoly(1,1)
pyplot.WorldSet( scratch , zfn)
scratch.mult(wholetilt)
m.add(scratch)
m.mult( mask)

implot.plotmap(m, colmap="heat", fout="gbtil/wholeap.eps/CPS",
               contours=implot.MkChopContours(m, ctype="lin"))

th1  =  pybnlib.TopHatDD()
th1.x0 = 0.5 * ParentRadius
th1.y0 = 0
th1.radius=0.5 * ParentRadius
mask1 = pyoof.Clone(m)
pyplot.WorldSet( mask1 , th1)
m.mult(mask1)

implot.plotmap(m, colmap="heat", fout="gbtil/apX.eps/CPS" ,
               contours=implot.MkChopContours(m, ctype="lin", nlevels=8))

tel1.MkFocMove(0.01,0,0,m)
m.add(scratch)
m.mult( mask)

th2  =  pybnlib.TopHatDD()
th2.y0 = 0.5 * ParentRadius
th2.radius=0.5 * ParentRadius
mask2 = pyoof.Clone(m)
pyplot.WorldSet( mask2 , th2)

m.mult(mask2)
implot.plotmap(m, colmap="heat", fout="gbtil/apY.eps/CPS",
               contours=implot.MkChopContours(m, ctype="lin", nlevels=5))











