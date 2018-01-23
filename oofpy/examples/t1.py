
import numpy
import scipy.optimize

from oofpy import zernike, amp, oof, telgeo, plot


# Params
wl=1.1e-3
R=3.0
NN=256
oversamp=2.0

g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                             -2*oversamp:2*oversamp:NN*1j], 0, -1)
z=zernike.ev(2,0,g)
z*=0
a=amp.gauss(0,0,1,0.3,0,0,g) * amp.dish(1.0,0, g)


dz=telgeo.primeF(14.4, g*R)
dzl=numpy.array([dz*0,
                 dz*-50e-3/wl * 2 *numpy.pi,
                 dz*50e-3/wl * 2 *numpy.pi])

x=oof.toskyDz(a, z, dzl)

f=oof.mkPredFn(2, g, dzl)

zz=numpy.array([0]*6 + [0,0,1,0.3, 0, 0])
zz[5]=1.0
borig=f(zz)
bnoise=borig+numpy.random.normal(0, borig.max()*0.05, borig.shape)

def fitfn(pars):
    return (bnoise-f(pars)).flatten()

x=scipy.optimize.leastsq(fitfn,
                         numpy.array([0]*6 + [0,0,1,0.3, 0, 0]),
                         full_output=True)

#plot.beams(f(numpy.array([0]*6 + [0,0,1,0.3, 0, 0])))
