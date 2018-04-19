# run with nix-shell  /home/bnikolic/n/oof/build/nix/oof.nix -A oofpyenv -j 2 --cores 6 --run "env OMP_NUM_THREADS=1 PYTHONPATH=$PYTHONPATH:/home/bnikolic/n/oof/oofpy/ python -i"
import imp # for reload
import json
import os

import numpy
import pandas
import scipy.optimize, scipy.stats

usepymp = False
# NB. This script uses pymp for parallelisation. However, scipy uses
# OpenMP in non-fork() safe way so nested scipy parallelisation should
# be disabled with MP_NUM_THREADS=1. Degree of parallelisation in
# scipy is trivial to what pymp can achieve
if usepymp:
    import pymp

import oofpy
from oofpy import zernike, amp, oof, telgeo, plot

from matplotlib import pylab

NTHREAD=50
SIGMAIL=0.72
# The primayr/secondary radius is 3m but the Lyot cold stop means only
# about 2.8m is illuminated
R=2.8


def mkPredFn(dz,
             nzern,
             wl,
             NN,
             oversamp):
    "Wrap the predictor fn"
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
           noisemult=0.05,
           noisedz=0,
           decimate=False,
           decimshift=0):
    """Compute retrieval error

    :param nzern: Maximum order of zernikes to include
    
    :param oversamp: Oversampling with respect to the Nyqyist sampling
    in the beam domain. *Note change of convention wrt OOF C++ code*
    
    :param nsim: Number of simulations to make

    :param NN: Number of pixels along the side of the beam maps
    
    :param dz: Defocus

    :param noisedz: Error in the defocus position: the simulated beams
    are additionally offset in focus by a random number drawn from
    normal distribution with this standard deviation

    """
    def mkBeams(noisedz):
        dzp=numpy.array(dz)
        if noisedz:
            dzp+=numpy.random.normal(0, noisedz,
                                     dzp.shape)
        f,pl,p0=mkPredFn(dz=dzp,
                         nzern=nzern,
                         wl=wl,
                         NN=NN,
                         oversamp=oversamp)
        return f, p0

    noisesn *= noiseF(wl=wl,
                      oversamp=oversamp,
                      NN=NN)    
    #f0 is the predict function without a defocus error
    f0, p0=mkBeams(0)
    borig=f0(p0)
    res=pymp.shared.array( (nsim,) + p0.shape )

    def dosim(p=False):
        numpy.random.seed()
        if p:
            prange=p.range(nsim)
        else:
            prange=range(nsim)
        for i in prange:
            if noisedz:
                # Make a predictor function with error in defocus and
                # simulate the observed beams using that
                f, _=mkBeams(noisedz)
                borig=f(p0)
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
                # Inner quarter of the map only. NB the fitting
                # function is f0, no focus error
                rres=plot.extract_mid((bnoise-f0(pars)), NN//4)
                if decimate:
                    # NB: The first dimension is the defocuses, which
                    # are not decimated
                    return rres[:, decimshift::decimate, decimshift::decimate].flatten()
                else:
                    return rres.flatten()

            x=scipy.optimize.leastsq(fitfn,
                                     p0,
                                     full_output=True)
            if x[-1] not in range(1,5):
                print ("Solution not converged!")
                res[i]=numpy.nan
            else:
                res[i]=x[0]
    if usepymp:
        with pymp.Parallel(NTHREAD) as p:
            dosim(p)
    else:
        dosim()

    return res

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


def wrms(xx,
         nzern):
    res=[]
    for i in range(xx.shape[0]):
        p, a = calcAp(xx[i],
                      nzern=nzern)
        res.append(weightedRMS(a, p))
    return numpy.array(res)


def dosim(dirout="sim",
          dz=100e-3,
          wl=1.1e-3):
    if not os.path.exists(dirout):
        os.makedirs(dirout)
    i=0
    pars= { "dz" : dz,
            "wl" : wl,
            "nsim": 50,
            "oversamp": 2.0}
    for nzern in range(4, 9):
        pars["nzern"]= nzern
        for sn in (1e-4, 3e-4, 6e-4, 1e-3, 3e-3, 6e-3, 1e-2, 3e-2, 6e-2):
            pars["noisesn"]=sn
            xx=retErr(**pars)
            numpy.savez("%s/sn%i-ret.npz" % (dirout, i), xx)
            open(os.path.join("%s/sn%i.json" % (dirout, i)), "w").write(json.dumps(pars))
            i+=1

def dosim2(dirout="sim2",
           wl=1.1e-3):
    if not os.path.exists(dirout):
        os.makedirs(dirout)    
    i=0
    pars= { "wl" : wl,
            "nsim": 50,
            "oversamp": 2.0,
            "nzern":6 }
    for dz in numpy.array([3, 10, 15, 30, 50, 80, 100, 300])*1e-3:
        pars["dz"]=dz
        for sn in (1e-3, 5e-3, 1e-2):
            pars["noisesn"]=sn
            xx=retErr(**pars)
            numpy.savez("%s/sn%i-ret.npz" %(dirout, i), xx)
            open(os.path.join("%s/sn%i.json" %(dirout,i)), "w").write(json.dumps(pars))
            i+=1            

def dosimdecim(dirout="simdecim",
               dz=100e-3):
    if not os.path.exists(dirout):
        os.makedirs(dirout)    
    i=0
    pars= { "dz" : dz,
            "wl" : 1.1e-3,
            "nsim": 50,
            "oversamp": 2.0,
            "nzern": 6}
    for sn in (1e-4, 3e-4, 6e-4, 1e-3, 3e-3, 6e-3, 1e-2):
        pars["noisesn"]=sn
        for d in [False, 2, 3, 4, 5, 6 ]:
            pars["decimate"]=d
            xx=retErr(**pars)
            numpy.savez("%s/sn%i-ret.npz" % (dirout, i), xx)
            open(os.path.join("%s/sn%i.json" % (dirout, i)), "w").write(json.dumps(pars))
            i+=1

def dosimdecimcheck(dirout="simdecimcheck",
                    dz=50e-3):
    if not os.path.exists(dirout):
        os.makedirs(dirout)    
    i=0
    pars= { "dz" : dz,
            "wl" : 1.1e-3,
            "nsim": 50,
            "oversamp": 2.0,
            "nzern": 6}
    for sn in (1e-4, ):
        pars["noisesn"]=sn
        for d in [3, 4, 5, 6 ]:
            for s in [0, 1, 2, 3, 4, 5]:
                pars["decimate"]=d
                pars["decimshift"]=s               
                xx=retErr(**pars)
                numpy.savez("%s/sn%i-ret.npz" % (dirout, i), xx)
                open(os.path.join("%s/sn%i.json" % (dirout, i)), "w").write(json.dumps(pars))
                i+=1
            
        
        
def dodznoisesim(dirout="simdznoise",
                 dz=50e-3):
    if not os.path.exists(dirout):
        os.makedirs(dirout)
    i=0
    pars= { "dz" : dz,
            "wl" : 1.1e-3,
            "nsim": 50,
            "oversamp": 2.0,
            "nzern": 6         }
    for sn in (1e-4, 3e-4, 6e-4, 1e-3, 3e-3, 6e-3):
        pars["noisesn"]=sn
        for dznoise in [0, 0.3e-3, 1e-3, 3e-3, 10e-3]:
            pars["noisedz"]=dznoise
            xx=retErr(**pars)
            numpy.savez("%s/sn%i-ret.npz" % (dirout, i), xx)
            open(os.path.join("%s/sn%i.json" % (dirout, i)), "w").write(json.dumps(pars))
            i+=1
            
            
            

if 0:
    xx=retErr(50e-3, nsim=100, oversamp=1.0, noisesn=0.05)
    numpy.savez("simaccbasic3.npz", xx)

if 0:
    xx=retErr(50e-3, nsim=100, oversamp=2.0, noisesn=0.05)
    numpy.savez("simaccbasic4.npz", xx)

if 0:
    dosim(dirout="sim3", dz=10e-3)



if 0:
    #ver 2. Checking for bug in oof.py. 
    dosim(dirout="v2-snsim-100",  dz=100e-3)
    dosim(dirout="v2-snsim-50",   dz=50e-3)
    dosim(dirout="v2-snsim-10",   dz=10e-3)
if 0:
    dosim2(dirout="v2-dz")
    dosim2(dirout="v2-dz035",  wl=0.35e-3)
if 0:    
    dosim2(dirout="v2-dz073",  wl=0.73e-3)    

if 0:
    dosimdecim("v2-simdecim-50", dz=50e-3)

if 0:
    dosimdecimcheck("v2-simdecimcheck")
    
if 0:
    dodznoisesim("v2-simnoisedz50", dz=50e-3)    

if 0:    
    dosimdecim("v2-simdecimdz10", dz=10e-3)
    dodznoisesim("v2-simdznoise")


if 0:
    dodznoisesim("v2-simnoisedz50", dz=50e-3)


if 0:
    dosim(dirout="v2-snsim-50-073",
          dz=50e-3,
          wl=0.73e-3)
if 0:
    dosim(dirout="v2-snsim-30-073",
          dz=30e-3,
          wl=0.73e-3)
    
    

def plotParDist(xx):
    for j in range(xx.shape[1]):
        pylab.clf()
        pylab.hist(xx[:,j])
        pylab.savefig(("par-%i-dist.png" % j))
    

#scipy.stats.mstats.normaltest(xx, axis=0)
        
        
