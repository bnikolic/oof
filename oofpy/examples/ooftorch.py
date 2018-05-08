import imp

import timeit
import math

import torch

import numpy

import oofpy
from oofpy import oof, zernike, oofacc, telgeo

from oofpy.oofacc import OO

SIGMAIL=0.72
R=2.8

import scipy
import scipy.optimize

def mkCFnT(nmax, a):
    """
    equivalent of zernike.mkCFn, but uses PyTORCH
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(zernike.ev(n, l, a))
    zz=numpy.array(zz)
    zz=numpy.moveaxis(zz, 0, -1)
    zz=OO(torch.from_numpy(zz).double())
    def lcfn(c):
        return (c*zz).sum(-1)
    lcfn.parnames=["z%i"%i for i in range(zz.shape[0])]
    return lcfn
    

def mkCFnN(nmax, a):
    """
    equivalent of zernike.mkCFn
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(zernike.ev(n, l, a))
    zz=numpy.array(zz)
    zz=numpy.moveaxis(zz, 0, -1)
    def lcfn(c):
        cc=c
        return (cc*zz).sum(axis=-1)
    lcfn.parnames=["z%i"%i for i in range(zz.shape[0])]
    return lcfn

def time_setup(nzmax,
               n=1024,
               dotorch=True):
    """ Run e.g., 
    timeit.timeit("x=ooftorch.cfn(ooftorch.z); x[0,0]", "import ooftorch; ooftorch.time_setup(6,256, dotorch=False)", number=100)

    timeit.timeit("x=ooftorch.cfn(ooftorch.z); x[0,0]", "import ooftorch; ooftorch.time_setup(6,256, dotorch=True)", number=100)
    """
    global cfn
    global z
    if dotorch:
        cfn=mkCFnT(nzmax, numpy.moveaxis(numpy.mgrid[-1:1:1024j, -1:1:1024j], 0, -1) )
        z=OO(torch.from_numpy(numpy.arange(zernike.N(nzmax))).double())
    else:
        cfn=mkCFnN(nzmax, numpy.moveaxis(numpy.mgrid[-1:1:1024j, -1:1:1024j], 0, -1) )
        z=(numpy.arange(zernike.N(nzmax)))
    

    
    
    
def mkPredFnT(dz,
              nzern,
              wl,
              NN,
              oversamp,
              dotorch=False):
    "Wrap the predictor fn"
    g=numpy.moveaxis(numpy.mgrid[-2*oversamp:2*oversamp:NN*1j,
                                 -2*oversamp:2*oversamp:NN*1j], 0, -1)
    dztemp=telgeo.primeF(14.4, g*R)
    dzl=numpy.array([dztemp*0,
                     dztemp*-1.0*dz/wl * 2 *numpy.pi,
                     dztemp*dz/wl * 2 *numpy.pi])

    nzpoly=zernike.N(nzern)
    initv=[0]*nzpoly + [0,0,1, SIGMAIL, 0, 0]

    if dotorch:
        dzl=OO(torch.from_numpy(dzl).double())
        f,pl=oofacc.mkPredFn(nzern,
                             g,
                             dzl,
                             numpy.array(initv),
                             omitp=["z0", "rho", "diff", "sigma"])
    else:
        f,pl=oof.mkPredFn(nzern,
                          g,
                          dzl,
                          numpy.array(initv),
                          omitp=["z0", "rho", "diff", "sigma"])
    p0=numpy.array([0]*(nzpoly-1) + [0,0, 1])
    return f, pl, p0



dz=50e-3
_nzern=False
wl=1.1e-3
_NN=False
oversamp=2

def setupfortime(NN, nzern):
    global bnoise, _NN, _nzern
    _NN=NN
    _nzern=nzern
    f0, p0=mkBeams(dotorch=False, NN=NN, nzern=_nzern)
    borig=f0(p0)
    noisesn =0.003
    noisemult=0.01
    noisesn *= 8.0
    bmax=borig.max()
    # Multiplicative noise
    bnoise=borig*(1+numpy.random.normal(0,
                                        noisemult,
                                        borig.shape))
    # Additive noise
    bnoise+=numpy.random.normal(0,
                                bmax*noisesn,
                                borig.shape)

    
    

def mkBeams(dotorch, NN, nzern):
    dzp=numpy.array(dz)
    f,pl,p0=mkPredFnT(dz=dz,
                      nzern=nzern,
                      wl=wl,
                      NN=NN,
                      oversamp=oversamp,
                      dotorch=dotorch)
    return f, p0


def dofit(dotorch,
          tol=1e-5):
    f0, p0=mkBeams(dotorch, _NN, _nzern)
    if dotorch:
        bnoisep=OO(torch.from_numpy(bnoise).double())
    else:
        bnoisep=bnoise
    def fitfn(pars):
        if dotorch:
            xx, x, fi=f0(pars)
            res=(bnoisep-xx)
            res=(res**2).sum()
            res.backward()
            return res.data.cpu().numpy(), x.grad[fi].data.cpu().numpy()
        else:
            res=(bnoisep-f0(pars)).flatten()
            res=-1*numpy.log(cauchy(res, gamma, 0 )).sum()
            return res
    if dotorch:
        res=scipy.optimize.minimize(fitfn,
                                    p0,
                                    method="BFGS",
                                    jac=True,
                                    tol=tol)    
    else:
        res=scipy.optimize.minimize(fitfn,
                                    p0,
                                    method='BFGS',
                                    jac=False,
                                    tol=tol)
    return res
    
