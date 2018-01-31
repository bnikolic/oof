
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

f,pl=oof.mkPredFn(2, g, dzl, numpy.array([0]*6 + [0,0,1,0.3, 0, 0]))

zz=numpy.array([0]*6 + [0,0,1,0.3, 0, 0])

# Use bclean to compute size of beam for ideal telescope
bclean=f(zz)
# Factor noise /beam -> /pixel  bclean[0].sum()/(bclean[0]**2).sum()**0.5

zz[5]=1.0
borig=f(zz)
bnoise=borig+numpy.random.normal(0, borig.max()*0.05, borig.shape)

f,pl=oof.mkPredFn(2, g, dzl, numpy.array([0]*6 + [0,0,1,0.3, 0, 0]),
                  omitp=["z0", "x0", "y0"])

def retErr(dz,
           nsim=50,
           wl=1.1e-3,
           NN=256,
           oversamp=2.0):
    """Compute retrieval error

    :param dz: Defocus
    
    """
    R=3.0
    g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                                 -2*oversamp:2*oversamp:NN*1j], 0, -1)
    dztemp=telgeo.primeF(14.4, g*R)
    dzl=numpy.array([dztemp*0,
                     dztemp*-1.0*dz/wl * 2 *numpy.pi,
                     dztemp*dz/wl * 2 *numpy.pi])

    initv=[0]*6 + [0,0,1,0.3, 0, 0]

    f,pl=oof.mkPredFn(2, g, dzl, numpy.array(initv),
                      omitp=["z0", "x0", "y0"])
    p0=numpy.array([0]*5 + [1,0.3, 0, 0])
    # Use bclean to compute size of beam for ideal telescope
    bclean=f(p0)
    # Factor noise /beam -> /pixel  bclean[0].sum()/(bclean[0]**2).sum()**0.5

    borig=f(p0)

    res=[]
    for i in range(nsim):
        bnoise=borig+numpy.random.normal(0,
                                         borig.max()*0.05,
                                         borig.shape)
        def fitfn(pars):
            return (bnoise-f(pars)).flatten()

        x=scipy.optimize.leastsq(fitfn,
                                 p0,
                                 full_output=True)
        res.append( x[0])
    return numpy.vstack(res)

    

#plot.beams(f(numpy.array([0]*6 + [0,0,1,0.3, 0, 0])))
