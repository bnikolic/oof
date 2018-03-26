# Accelerated OOF

import numpy

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
    
