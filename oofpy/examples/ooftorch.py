import timeit

import torch

from torch.autograd import Function, Variable

import pytorch_fft.fft.autograd as fft
import numpy

import oofpy
from oofpy import oof, zernike, oofacc, telgeo

SIGMAIL=0.72
R=2.8



if 0:
    # Toy examples
    Ft=fft.Fft2d()
    X = Variable(torch.randn(3, 3, 3).double().cuda(), requires_grad=True)
    Y = Ft(X, X)
    Z = (Y[0])**2

def mkCFnT(nmax, a):
    """
    equivalent of zernike.mkCFn
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(zernike.ev(n, l, a))
    zz=numpy.array(zz)
    zz=numpy.moveaxis(zz, 0, -1)
    zz=torch.from_numpy(zz).double().cuda()
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
        z=torch.from_numpy(numpy.arange(zernike.N(nzmax))).double().cuda()
    else:
        cfn=mkCFnN(nzmax, numpy.moveaxis(numpy.mgrid[-1:1:1024j, -1:1:1024j], 0, -1) )
        z=(numpy.arange(zernike.N(nzmax)))
    

    
    
    
def mkPredFnT(dz,
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
    dzl=Variable(torch.from_numpy(dzl).float().cuda())

    nzpoly=zernike.N(nzern)
    initv=[0]*nzpoly + [0,0,1, SIGMAIL, 0, 0]

    f,pl=oofacc.mkPredFn(nzern,
                         g,
                         dzl,
                         numpy.array(initv),
                         omitp=["z0", "rho", "diff"])
    p0=numpy.array([0]*(nzpoly-1) + [0,0, 1, SIGMAIL])
    return f, pl, p0

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


if 1:
    f, p, i=mkPredFnT(50e-3, 2,  1.1e-3, 128, 2.0)    
    with torch.autograd.profiler.profile() as prof:
        yy, x=f(i)
        zz=(yy**2).sum()
        zz.backward()
    print(prof)

if 0:
    f, p, i=mkPredFnT(50e-3, 7,  1.1e-3, 512, 2.0)    
    with torch.cuda.profiler.profile():
        yy, x=f(i)
        zz=(yy**2).sum()
        zz.backward()
        with torch.autograd.profiler.emit_nvtx():
            yy, x=f(i)
            zz=(yy**2).sum()
            zz.backward()

