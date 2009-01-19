"""
Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>

Decompose the GBT defocus (as implemented in OOF) into Zernike
coefficients. Make use of orthonormality of Zernike's, so only need to
compute the overlap integrals.

"""

import setup
import pyoof
import pyplot
import pybnlib

import ooffitconv

def MkZernPoly(n,l,
               npix=512):
    zmap=pyplot.Map(npix,
                    npix)
    pyplot.MkApCS(zmap,
                  1.0)
    zfn=pybnlib.ZernPoly(n,l)
    pyplot.WorldSet(zmap,
                    zfn)
    return zmap
    

def GBTDefocMap(do90=False,
                npix=512):
    if do90:
        tel1=pyoof.TruncGBT(45)
    else:
        tel1=pyoof.GBTGeo()
    aperture=pyplot.Map(npix,
                        npix)
    pyplot.MkApCS(aperture,
                  tel1.DishEffRadius())
    tel1.MkDefocus(1,
                   aperture)
    mask=pyplot.Clone(aperture)
    tel1.DishMask(mask)
    aperture.mult(mask)    
    return aperture, mask

def Overlap(n,l,
            do90=False,
            npix=512):
    """
    Calculate overlap between Zernike polynomial and a defocus of unit
    magnitude
    """
    df,mask=GBTDefocMap(do90=do90,
                        npix=npix)
    zm=MkZernPoly(n,l,
                  npix=npix)
    zm.mult(mask)
    df.mult(zm)
    overlap=df.sum()
    zm.mult(zm)
    norm=zm.sum()
    return overlap/norm

def Decompose(nzmax=5,
              **kwargs):
    """
    Decompose the defocus into zernike coefficients
    
    :param nzmax: Maximum order to use
    
    :param do90: Do the procedure for the 90-m parameterisation and
    illumination

    :returns: Dictionary of zernike coefficients representing unit
    defocus

    Example:
    
    >>> Decompose(do90=True)


    """
    res={}
    for n in range(2,
                   nzmax+1):
        for l in range(-n,n+1,2):
            x=Overlap(n,l,
                      **kwargs)
            k=ooffitconv.OOFnltoOOFk(n,l)
            res["z%i"%k]=x
            print "n=%i l=%i , k=%i, coeff: %g" % (n, l,
                                                   k,
                                                   x
                                                   )
    return res

    
    
    


