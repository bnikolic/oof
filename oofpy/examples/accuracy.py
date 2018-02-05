import numpy
import scipy.optimize, scipy.stats
import pymp

import oofpy
from oofpy import zernike, amp, oof, telgeo, plot

from matplotlib import pylab

def retErr(dz,
           nzern=4,
           nsim=50,
           wl=1.1e-3,
           NN=256,
           oversamp=2.0):
    """Compute retrieval error

    :param nzern: Maximum order of zernikes to include
    
    :param oversamp: Oversampling with respect to the Nyqyist sampling
    in the beam domain. *Note change of convention wrt OOF C++ code*
    
    :param nsim: Number of simulations to make

    :param NN: Number of pixels along the side of the beam maps
    
    :param dz: Defocus

    """
    R=3.0
    g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                                 -2*oversamp:2*oversamp:NN*1j], 0, -1)
    dztemp=telgeo.primeF(14.4, g*R)
    dzl=numpy.array([dztemp*0,
                     dztemp*-1.0*dz/wl * 2 *numpy.pi,
                     dztemp*dz/wl * 2 *numpy.pi])

    nzpoly=zernike.N(nzern)
    initv=[0]*nzpoly + [0,0,1,0.3, 0, 0]

    f,pl=oof.mkPredFn(nzern,
                      g,
                      dzl,
                      numpy.array(initv),
                      omitp=["z0", "rho", "diff"])
    p0=numpy.array([0]*(nzpoly-1) + [0,0, 1,0.3])
    # Use bclean to compute size of beam for ideal telescope
    bclean=f(p0)
    # Factor noise /beam -> /pixel  bclean[0].sum()/(bclean[0]**2).sum()**0.5

    borig=f(p0)

    res=pymp.shared.list()
    with pymp.Parallel(4) as p:
        for i in p.range(nsim):
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

if 0:
    xx=retErr(50e-3, nsim=500)
    numpy.savez("simaccbasic3.npz", xx)

def plotParDist(xx):
    for j in range(xx.shape[1]):
        pylab.clf()
        pylab.hist(xx[:,j])
        pylab.savefig(("par-%i-dist.png" % j))
    
#        scipy.mstats.normaltest(a, axis=0)[source]¶
        
        
