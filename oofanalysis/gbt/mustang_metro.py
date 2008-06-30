# Bojan Nikolic  <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Investigate MUSTANG OOF data using the Metropolis MCMC algorithm

import setup

import pybnmin1
import bnmin1utils
import bnmin1io

import oofreduce

def MetroMustang(fnamein,
                 amp_sigma=0.00001,
                 z_sigma=0.05,
                 nsample=100,
                 ic=None,
                 fnameout_chain=None):
    """
    Sample posterior distribution given MUSTANG data using the
    Metropolis MCMC algorithm

    :param amp_sigma: Standard deviation of the proposal distribution
    for aperture function amplitude
    
    :param z_sigma: Standard deviation of the proposal distribution
    for the coefficients of Zernikes

    :param nsample: The number of proposals to make

    :param ic: The initial condition to start the chain from. So far
    support a FITS file containing the fit as output by FSave from
    bnmin1io

    :param fnameout_chain: Name of FITS file to which the calculated
    chain should be written to.
    
    :returns: The calculated chain 
    """
    
    oc=oofreduce.MkObsCompare( fnamein, 
                               nzern=5)

    sigmas=pybnmin1.DoubleVector([ amp_sigma]+ [z_sigma]*20 )

    metro=pybnmin1.MetropolisMCMC(oc.downcast(),
                                  sigmas,
                                  33)
    if ic is not None:
        bnmin1io.FLoad(metro,
                       ic)
    else:
        metro.getbyname("amp").setp(0.0001)

    chain=metro.sample(nsample)    
    if fnameout_chain:
        bnmin1io.fSaveChain(metro, chain, 
                            fnameout_chain)
    return chain
    

def TestMetro():

    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.02,
                        nsample=10)

def TestMetroIC():
    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.01,
                        nsample=10000,
                        ic="oofout/t18-raw-5-3-db-000/z5/fitpars.fits",
                        fnameout_chain="temp/metro_ic.fits")

