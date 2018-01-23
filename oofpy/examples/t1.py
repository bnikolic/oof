
import numpy

from oofpy import zernike, amp, oof, telgeo

g=numpy.moveaxis(numpy.mgrid[-2:2:128j, -2:2:128j], 0, -1)
z=zernike.ev(2,0,g)
a=amp.gauss(0,0,1,1,0,0,g) * amp.dish(1.0,0, g)

dz=telgeo.primeF(14.4, g)

                 
