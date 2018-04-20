import timeit

import torch

from torch.autograd import Function, Variable

import pytorch_fft.fft.autograd as fft
import numpy

import oofpy
from oofpy import oof, zernike, oofacc, telgeo

SIGMAIL=0.72
R=2.8

import scipy
import scipy.optimize

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
        dzl=Variable(torch.from_numpy(dzl).double().cuda())
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
nzern=5
wl=1.1e-3
NN=512
oversamp=2

def mkBeams(dotorch=False):
    dzp=numpy.array(dz)
    f,pl,p0=mkPredFnT(dz=dz,
                      nzern=nzern,
                      wl=wl,
                      NN=NN,
                      oversamp=oversamp,
                      dotorch=dotorch)
    return f, p0

f0, p0=mkBeams()
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


def dofit(dotorch,
          tol=1e-5):
    f0, p0=mkBeams(dotorch)
    if dotorch:
        bnoisep=Variable(torch.from_numpy(bnoise).double().cuda())
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
            res=(bnoisep-f0(pars))
            res=(res**2).sum()
            return res
    if dotorch:
        res=scipy.optimize.minimize(fitfn,
                                    p0,
                                    method="BFGS",
                                    jac=True,
                                    tol=tol,
                                    options={'eps': 0.001})    
    else:
        res=scipy.optimize.minimize(fitfn, p0,
                                    method='BFGS',
                                    jac=False,
                                    tol=tol)
    return res
    




if 0:
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
            for i in range(1000):
                yy, x=f(i)
                zz=(yy**2).sum()
                zz.backward()


# pip install --upgrade --upgrade-strategy "only-if-needed" --force-reinstall --no-binary :all: /home/bnikolic/work/pytorch_fft/dist/pytorch_fft-0.14-cp27-cp27mu-linux_x86_64.whl
# (cd /home/bnikolic/work/pytorch_fft/; rm -r build && python setup.py build_ext && python setup.py bdist_wheel)                
# PYTHONPATH=$PYTHONPATH:/home/bnikolic/work/oof/oofpy/:/home/bnikolic/pytorch/lib/python2.7/site-packages/ nvprof --profile-from-start off -o trace11.prof -- python  /home/bnikolic/work/oof/oofpy/examples/ooftorch.py                
# e.g. PYTHONPATH=$PYTHONPATH:/home/bnikolic/work/oof/oofpy/:/home/bnikolic/pytorch/lib/python2.7/site-packages/ perf record  -- python  /home/bnikolic/work/oof/oofpy/examples/ooftorch.py                


if 0:
    f, p, i=mkPredFnT(50e-3, 3,  1.1e-3, 512, 2.0)
    def sfn(pp):
        yy, x, fi=f(pp)
        zz=(yy**2).sum()
        zz.backward()
        return zz.data.cpu().numpy(), x.grad[fi].data.cpu().numpy()
    res2=scipy.optimize.minimize(sfn, i,
                                method="BFGS",
                                jac=True,
                                tol=1e-12)

if 0:
    f, p, i=mkPredFn(50e-3, 3,  1.1e-3, 512, 2.0)
    def sfn(pp):
        yy, x, fi=f(pp)
        zz=(yy**2).sum()
        return zz
    res=scipy.optimize.minimize(sfn, ii,
                                method='BFGS',
                                jac=False,
                                tol=1e-10,
                                options={'eps': 0.001})

    # NB: with finite diff jacobian, need to set the EPS value:
# res=scipy.optimize.minimize(sfn, ii,  method='BFGS', jac=False, tol=1e-10, options={'eps': 0.001})
