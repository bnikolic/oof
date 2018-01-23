import numpy

import zernike, amp

def tosky(a,p):
    """FFT to sky"""
    return numpy.fft.fftshift(numpy.fft.ifft2(numpy.fft.ifftshift(a * numpy.exp(1j*p)))).real

def toskyDz(a, p, dz):
    """Predict beam maps including a defocus
    
    :param dz: 3d array with outermost dimension representing the
    different defocus settings
    """
    res=[]
    for i in range(dz.shape[0]):
        res.append(tosky(a, p+dz[i]))
    return numpy.array(res)

def mkPredFn(nzern, g, dzl):
    zlc=zernike.mkCFn(nzern, g)
    nzpoly=zernike.N(nzern)
    def f(pars):
        p=zlc(pars[0:nzpoly])
        a=amp.gauss(* (list(pars[nzpoly:]) +[g]))
        return toskyDz(a, p, dzl)
    return f
