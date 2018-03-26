# Accelerated OOF

import numpy

def cfftshift(x, axes=None):
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
    # Rewrite in terms of torch.cat and torch.split
    for k in axes:
        n = shape[k]
        pp = (n+1)//2
        p1,p2 = torch.split( y, pp, dim=k)
        y=torch.cat((p2,p1,), dim=k)
    return y
    
