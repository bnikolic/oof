
import numpy

from oofpy import zernike, amp, oof, telgeo, plot

g=numpy.moveaxis(numpy.mgrid[-2:2:128j, -2:2:128j], 0, -1)
z=zernike.ev(2,0,g)
z*=0
a=amp.gauss(0,0,1,0.3,0,0,g) * amp.dish(1.0,0, g)

wl=1.1e-3

dz=telgeo.primeF(14.4, g)
dzl=numpy.array([dz*0,
                 dz*-500e-3/wl * 2 *numpy.pi,
                 dz*500e-3/wl * 2 *numpy.pi])

x=oof.toskyDz(a, z, dzl)                 
