# Bojan Nikolic  <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Investigate MUSTANG OOF data using the Metropolis MCMC algorithm

import setup

import os

import pybnmin1
import bnmin1utils
import bnmin1io

import oofreduce
import pyxplot
import pyfits

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
                                  33,
                                  pybnmin1.MetropolisMCMC.Sequence)
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

def plotSinlgeParDist(din,
                      parname,
                      fnameout):
    """
    Plot the distribution of a single parameter
    """
    d=din.data.field(parname)
    pyxplot.histogram( [ (d, "")],
                       fnameout,
                       xax=pyxplot.axis(parname),
                       width=pyxplot.MNRAS_SC,
                       nbins=20,
                       key=None)


def plotParDist(fnamein,
                dirout):
    """
    Plot the distribution of each parameter from a chain stored in a
    fits file. 
    """
    din=pyfits.open(fnamein)[1]
    for pname in din.get_coldefs().names:
        plotSinlgeParDist(din,
                          pname,
                          os.path.join(dirout, 
                                       "p%s-dist.eps" % (pname,)))

    
                

def TestMetro():

    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.02,
                        nsample=10,
                        fnameout_chain="temp/t.fits")

def TestMetroIC():
    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.1,
                        nsample=20000,
                        ic="oofout/t18-raw-5-3-db-000/z5/fitpars.fits",
                        fnameout_chain="temp/metro_ic.fits")

def TestMetroIC2():
    return MetroMustang("td/t18-raw-5-1-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.1,
                        nsample=20000,
                        ic="oofout/t18-raw-5-1-db-000/z5/fitpars.fits",
                        fnameout_chain="temp/metro_ic2.fits")

def TestMetroIC3():
    return MetroMustang("td/t18-raw-6-2-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.1,
                        nsample=20000,
                        ic="oofout/t18-raw-6-2-db-000/z5/fitpars.fits",
                        fnameout_chain="temp/metro_ic3.fits")

