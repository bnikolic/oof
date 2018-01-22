import numpy

def tosky(a,p):
    """FFT to sky"""
    return numpy.fft.fftshift(numpy.fft.ifft2(numpy.fft.ifftshift(a * numpy.exp(p))))
    
