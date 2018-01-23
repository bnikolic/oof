import numpy

def tosky(a,p):
    """FFT to sky"""
    return numpy.fft.fftshift(numpy.fft.ifft2(numpy.fft.ifftshift(a * numpy.exp(1j*p))))

def toskyDz(a, p, dz):
    """Predict beam maps including a defocus
    
    :param dz: 3d array with outermost dimension representing the
    different defocus settings
    """
    res=[]
    for i in range(dz.shape[0]):
        res.append(tosky(a, p+dz[i]))
    return numpy.array(res)
