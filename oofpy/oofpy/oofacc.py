# Accelerated OOF

import numpy
import pytorch_fft.fft.autograd as fft
from torch.autograd import Variable

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
    Ft=fft.Ifft2d()
    s=a*torch.cos(p)
    c=a*torch.sin(p)
    R=Ft(torch.unsqueeze(cifftshift(s), 0),
         torch.unsqueeze(cifftshift(c), 0))
    S=map(cfftshift, R)
    return S[0]**2 + S[1]**2

    
