import math

import pyplot
import pyoof
import implot
import pybnlib

tel1=pyoof.GBTGeo()

npix =256

aperture = pyplot.Map(npix, npix)
pyplot.MkApCS(aperture, 70)

aperture2 = pyplot.Map(npix, npix)
pyplot.MkApCS(aperture2, 70)

mask=pyoof.Clone(aperture)
tel1.DishMask(mask)

pistmap=pyplot.Map(npix, npix)
pyplot.MkApCS(pistmap, 70)
zfn=pybnlib.ZernPoly(0,0)
pyplot.WorldSet( pistmap , zfn)
pistmap.mult(-1.7)


tiltmap=pyplot.Map(npix, npix)
pyplot.MkApCS(tiltmap, 70)
zfn=pybnlib.ZernPoly(1,1)
pyplot.WorldSet( tiltmap , zfn)
#tiltmap.mult(-0.012)
#tiltmap.mult(+0.012)
tiltmap.mult(0)

tel1.MkSubMove( 0 , 1 , 0 , aperture )
aperture.add(tiltmap)
aperture.add(pistmap)
aperture.mult(mask)

tel1.MkDefocus( 1, aperture2)
aperture2.add(pistmap)
aperture2.mult(mask)
