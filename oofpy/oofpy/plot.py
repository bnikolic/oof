# Plotting routines
import numpy

import matplotlib.pyplot as p

def extract_mid(a, npixel):
    """
    Extract a section from middle of a map

    Suitable for zero frequencies at npixel/2. This is the reverse
    operation to pad.

    .. note::
    
        Only the two innermost axes are transformed

    :param npixel: desired size of the section to extract
    :param a: grid from which to extract
    """
    ny, nx = a.shape[-2:]
    cx = nx // 2
    cy = ny // 2
    s = npixel // 2
    if npixel % 2 != 0:
        return a[..., cx - s:cx + s + 1, cy - s:cy + s + 1]
    else:
        return a[..., cx - s:cx + s, cy - s:cy + s]



def aplane(a, ph, fnameout="aplane.png"):
    fig=p.figure(figsize=(7,3))
    ax=fig.add_subplot(1, 2, 1)
    m=ax.imshow(a)
    p.colorbar(m)
    p.title("Aperture plane amplitude")
    ax=fig.add_subplot(1, 2, 2)
    m=ax.imshow(ph)
    p.colorbar(m)
    p.title("Aperture plane phase")    
    p.savefig(fnameout)
    p.close()

def beams(a, fnameout="beams.png",
          oversamp=1.0):
    fig=p.figure(figsize=(12,3), dpi=150)
    N=a.shape[0]
    NN=a.shape[1]
    for i in range(N):
        ax=fig.add_subplot(1, N, i+1)
        m=ax.imshow(extract_mid(a[i], NN//4).real,
                    extent=numpy.array([-1, 1, -1, 1])* NN//4 /oversamp,
                    interpolation="none")
        p.colorbar(m)
    p.savefig(fnameout)
    p.close()

def screens(a, fnameout="screens.png"):
    fig=p.figure()
    N=a.shape[0]
    for i in range(N):
        ax=fig.add_subplot(1, N, i+1)
        m=ax.imshow(a[i].real)
        p.colorbar(m)
    p.savefig(fnameout)
    p.close()
    
