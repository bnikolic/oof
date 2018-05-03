# Accelerated OOF
import inspect

import numpy
import torch

from . import zernike, amp

def abs2(x):
    "Power after an fft"
    return (x**2).sum(dim=-1)

def OO(x):
    "offload, maybe"
    if 0:
        return x.cuda()
    else:
        return x

def cfftshift(x, axes=None,
              invert=False):
    """
    Like numpy.fft.fftshift, but pyTorch
    """
    shape= x.shape    
    ndim = len(shape)
    if axes is None:
        axes = list(range(ndim))
    elif isinstance(axes, integer_types):
        axes = (axes,)
    y = x
    for k in axes:
        n = shape[k]
        if invert:
            pp = n-(n+1)//2
        else:
            pp = (n+1)//2
        pl= torch.split( y, pp, dim=k)
        y= torch.cat(pl[1:]+(pl[0], ),
                    dim=k)
    return y

def cifftshift(*args, **kwargs):
    return cfftshift(*args, invert=True, **kwargs)

# E.g. compare with: tosky(x,y).data.cpu().numpy() - oofpy.oof.tosky(x.data.cpu().numpy(),y.data.cpu().numpy())
def tosky(a, p):
    """
    see oof.tosky
    """
    s=a*torch.cos(p)
    c=a*torch.sin(p)
    S=torch.fft(torch.stack([s,p], dim=-1),
                signal_ndim=2)
    return cfftshift(abs2(S))

def toskyDz(a, p, dz):
    """
    See oof.toskyDz
    """
    res=[]
    for i in range(dz.shape[0]):
        res.append(tosky(a, p+dz[i]))
    return torch.stack(res)


def toskyDzF(a, p, dz):
    """Like See toskyDz but faster by batching.

    Big saving, presumably due to the overhead of creating the cufft
    plan?
    """
    res=[]
    RR, II = [], []
    for i in range(dz.shape[0]):
        pp=p+dz[i]
        RR.append(a*torch.cos(pp))
        II.append(a*torch.sin(pp))
    R=torch.fft(torch.stack([torch.stack(RR), torch.stack(II)], dim=-1),
                signal_ndim=2)
    for i in range(dz.shape[0]):
        res.append( cfftshift( abs2(R[i])))
    return torch.stack(res)


def mkCFn(nmax, a):
    """see oof.mkCFn
    """
    zz=[]
    for n in range(nmax+1):
        for l in range(-n, n+1, 2):
            zz.append(zernike.ev(n, l, a))
    N=len(zz)
    zz=numpy.moveaxis(numpy.array(zz), 0, -1)
    zz=OO(torch.from_numpy(zz).double())
    def lcfn(c):
        return (c*zz).sum(-1)
    lcfn.parnames=["z%i"%i for i in range(N)]
    return lcfn

def hypot(x, y):
    return torch.sqrt(x**2 + y**2)

def gauss(x0, y0, amp, sigma, rho, diff, a):
    dx=a[...,0]-x0
    dy= a[...,1]-y0
    r=hypot(dx, dy)
    # NB: multiplying with scalar gives  a cpu tensor?
    return OO(amp*torch.exp(-1.0/ (2*sigma**2) * (r**2 +
                                                  OO(rho*(dx*dy))+
                                                  OO(diff*(dx**2-dy**2)))))

def dish(R, S, a):
    """
    """
    r=hypot(a[...,0], a[...,1])
    res=(r<=R)
    if S>0:
        res*=(r>S)
    return res

def mkPredFn(nzern, g, dzl,
             initv,
             omitp=[],
             pdish=None):
    """
    see oof.mkPredFn()
    """
    # Make our own copy
    initv=numpy.array(initv)
    # Use the accellerated zernike calculation
    zlc=mkCFn(nzern, g)
    nzpoly=zernike.N(nzern)
    # This is the list of all parameter names
    parl=zlc.parnames+inspect.getargspec(gauss).args[:-1]
    # Indices of params we will fit for
    fiti=numpy.array([i for i,xz in enumerate(parl) if  xz not in omitp])
    if pdish is None:
        pdish=OO(torch.from_numpy(amp.dish(1, 0, g)*1.0).double())
    g=OO(torch.from_numpy(g).double())
    def f(pars):
        initv[fiti]=pars
        initvv=OO(torch.tensor(initv,
                               requires_grad=True).double())
        p=zlc(initvv[0:nzpoly])
        a=gauss(* (list(initvv[nzpoly:]) +[g])) * pdish
        return toskyDzF(a, p, dzl), initvv, fiti
    return f, numpy.array(parl)[fiti]





