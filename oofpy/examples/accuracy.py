import imp # for reload
import json

import numpy
import pandas
import scipy.optimize, scipy.stats
import pymp

import oofpy
from oofpy import zernike, amp, oof, telgeo, plot

from matplotlib import pylab

NTHREAD=20
SIGMAIL=0.72

def mkPredFn(dz,
             nzern,
             wl,
             NN,
             oversamp):
    "Wrap the predictor fn"
    R=3.0
    g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                                 -2*oversamp:2*oversamp:NN*1j], 0, -1)
    dztemp=telgeo.primeF(14.4, g*R)
    dzl=numpy.array([dztemp*0,
                     dztemp*-1.0*dz/wl * 2 *numpy.pi,
                     dztemp*dz/wl * 2 *numpy.pi])

    nzpoly=zernike.N(nzern)
    initv=[0]*nzpoly + [0,0,1, SIGMAIL, 0, 0]

    f,pl=oof.mkPredFn(nzern,
                      g,
                      dzl,
                      numpy.array(initv),
                      omitp=["z0", "rho", "diff"])
    p0=numpy.array([0]*(nzpoly-1) + [0,0, 1, SIGMAIL])
    return f, pl, p0

def retErr(dz,
           nzern=4,
           nsim=50,
           wl=1.1e-3,
           NN=256,
           oversamp=2.0,
           noisesn=0.05,
           noisemult=0.05):
    """Compute retrieval error

    :param nzern: Maximum order of zernikes to include
    
    :param oversamp: Oversampling with respect to the Nyqyist sampling
    in the beam domain. *Note change of convention wrt OOF C++ code*
    
    :param nsim: Number of simulations to make

    :param NN: Number of pixels along the side of the beam maps
    
    :param dz: Defocus

    """
    f,pl,p0=mkPredFn(dz=dz,
                     nzern=nzern,
                     wl=wl,
                     NN=NN,
                     oversamp=oversamp)

    noisesn *= noiseF(wl=wl,
                      oversamp=oversamp,
                      NN=NN)    

    borig=f(p0)

    res=pymp.shared.list()
    with pymp.Parallel(NTHREAD) as p:
        numpy.random.seed()
        for i in p.range(nsim):
            bmax=borig.max()
            # Multiplicative noise
            bnoise=borig*(1+numpy.random.normal(0,
                                                noisemult,
                                                borig.shape))
            # Additive noise
            bnoise+=numpy.random.normal(0,
                                        bmax*noisesn,
                                        borig.shape)
            def fitfn(pars):
                return (bnoise-f(pars)).flatten()

            x=scipy.optimize.leastsq(fitfn,
                                     p0,
                                     full_output=True)
            res.append( x[0])
    return numpy.vstack(res)

def noiseF(wl=1.1e-3,
           NN=256,
           oversamp=2.0):
    """Calculate the factor by which  per-pixel noise  is greater than the per-beam noise"""
    f,pl,p0=mkPredFn(dz=0,
                     nzern=1,
                     wl=wl,
                     NN=NN,
                     oversamp=oversamp)
    bclean=f(p0)
    return bclean[0].sum()/((bclean[0]**2).sum()**0.5)

def calcAp(p,
           nzern=4,
           NN=256,
           oversamp=2.0):
    R=3.0
    g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                                 -2*oversamp:2*oversamp:NN*1j],
                     0,
                     -1)
    zlc=zernike.mkCFn(nzern, g)
    nzpoly=zernike.N(nzern)    
    return (zlc(numpy.array([0]+list(p[0:nzpoly-1]))) * amp.dish (1.0, 0, g) ,
            amp.gauss(0,0,1, SIGMAIL, 0, 0, g) * amp.dish (1.0, 0, g))

def weightedRMS(a, p):
    return ( p**2*a/a.sum() ).sum()**0.5


def wrms(xx):
    res=[]
    for i in range(xx.shape[0]):
        p, a = calcAp(xx[i])
        res.append(weightedRMS(a, p))
    return numpy.array(res)


def dosim():
    dirout="sim"
    i=0
    pars= { "dz" : 50e-3,
            "wl" : 1.1e-3,
            "nsim": 20,
            "oversamp": 2.0}
    for nzern in range(4, 9):
        pars["nzern"]= nzern
        for sn in (1e-4, 3e-4, 6e-4, 1e-3, 3e-3, 6e-3, 1e-2, 3e-2, 6e-2):
            pars["noisesn"]=sn
            xx=retErr(**pars)
            numpy.savez("sim/sn%i-ret.npz" %i, xx)
            open(os.path.join("sim/sn%i.json" %i), "w").write(json.dumps(pars))
            i+=1
            
def wrmssim():
    i=0
    res=[]
    while os.path.exists("sim/sn%i.json" %i):
        p=json.load(open("sim/sn%i.json" %i))
        xx=numpy.load("sim/sn%i-ret.npz" %i)['arr_0']
        zz=wrms (xx)
        p["wrms"]=zz.mean()
        p["wrmserr"]=zz.std()/zz.shape[0]**0.5
        res.append(p)
        i+=1
    return pandas.DataFrame(res)
    
            
            

if 0:
    xx=retErr(50e-3, nsim=100, oversamp=1.0, noisesn=0.05)
    numpy.savez("simaccbasic3.npz", xx)

if 0:
    xx=retErr(50e-3, nsim=100, oversamp=2.0, noisesn=0.05)
    numpy.savez("simaccbasic4.npz", xx)

def plotParDist(xx):
    for j in range(xx.shape[1]):
        pylab.clf()
        pylab.hist(xx[:,j])
        pylab.savefig(("par-%i-dist.png" % j))
    

#scipy.stats.mstats.normaltest(xx, axis=0)
        
        
