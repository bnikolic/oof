# Accelerated OOF
import inspect

import numpy
import torch
import pytorch_fft.fft.autograd as fft
from torch.autograd import Variable

import zernike, amp

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
    Ft=fft.Ifft2d()
    s=a*torch.cos(p)
    c=a*torch.sin(p)
    s=torch.unsqueeze(cifftshift(s), 0)
    c=torch.unsqueeze(cifftshift(c), 0)
    R=Ft(s,
         c)
    S=map(cfftshift, R)
    return S[0]**2 + S[1]**2

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
    Ft=fft.Ifft2d()    
    res=[]
    RR, II = [], []
    for i in range(dz.shape[0]):
        pp=p+dz[i]
        RR.append(a*torch.cos(pp))
        II.append(a*torch.sin(pp))
    R=Ft(torch.stack(RR), torch.stack(II))
    for i in range(dz.shape[0]):
        S=map(cfftshift, (R[0][i], R[1][i]))
        res.append(S[0]**2 + S[1]**2)    
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
    zz=Variable(torch.from_numpy(zz).float().cuda())
    def lcfn(c):
        #c=torch.from_numpy(c).float().cuda()
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
    return (amp*torch.exp(-1.0/ (2*sigma**2) * (r**2 +
                                                (rho*(dx*dy)).cuda()+
                                                (diff*(dx**2-dy**2)).cuda()))).cuda()

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
        pdish=Variable(torch.from_numpy(amp.dish(1, 0, g)*1.0).float().cuda())
    g=Variable(torch.from_numpy(g).float().cuda())
    def f(pars):
        initv[fiti]=pars
        initvv=Variable(torch.from_numpy(numpy.array(initv)).float().cuda(),
                        requires_grad=True)
        p=zlc(initvv[0:nzpoly])
        a=gauss(* (list(initvv[nzpoly:]) +[g])) * pdish
        return toskyDzF(a, p, dzl), initvv
    return f, numpy.array(parl)[fiti]




