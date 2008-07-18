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
from pyhlp import twod
import pyfits

def MetroMustang(fnamein,
                 amp_sigma=0.00001,
                 z_sigma=0.05,
                 nsample=100,
                 ic=None,
                 fnameout_chain=None,
                 nzern=5,
                 multiamp=False):
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
    
    :param nzern: The order of Zernike polynimals to fit to.

    :param multiamp: Fit for the relative amplitudes of the maps
    
    :returns: The calculated chain 
    """

    if multiamp is False:
        oc=oofreduce.MkObsCompare(fnamein, 
                                  nzern=nzern)
    else:
        oc=oofreduce.MkObsCompare(fnamein, 
                                  nzern=nzern,
                                  nobs=3)
        
    nzc_d= {1: 2,
            2: 5,
            3 : 9,
            5 : 20}

    sigmal=[ amp_sigma]+ [z_sigma]*nzc_d[nzern]
    if multiamp is not False:
        sigmal.extend([0.01]*(3-1))    
    sigmas=pybnmin1.DoubleVector(sigmal)

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

def medianPars(fnamein,
               burn=0):
    """
    Return the median value of each parameter in a chain
    """
    din=pyfits.open(fnamein)[1]
    res={}
    for n in din.data.names:
        fd=din.data.field(n)
        res[n]=numpy.median(fd[burn*len(fd):])
    return res

def escapeAxisName(n):
    """Escape LaTeX control characters"""
    n=n.replace(r"_",r"\_")
    return n
    
def plotSinlgeParDist(din,
                      parname,
                      fnameout,
                      burn=0):
    """
    Plot the distribution of a single parameter
    """
    d=din.data.field(parname)
    x=d[burn*len(d):]
    pyxplot.histogram( [ (x, "")],
                       fnameout,
                       xax=pyxplot.axis(escapeAxisName(parname)),
                       width=pyxplot.MNRAS_SC,
                       nbins=20,
                       key=None)

def plotTwoPar(din,
               p1, p2,
               fnameout,
               burn=0):
    d1,d2=[din.data.field(x) for x in [p1,p2]]
    x1=d1[burn*len(d1):]
    x2=d2[burn*len(d2):]
    
    twod.hist2d(x1,x2,
                fnameout,
                xlabel=escapeAxisName(p1),
                ylabel=escapeAxisName(p2),
                bins=20)


def plotParDist(fnamein,
                dirout,
                burn=0):
    """
    Plot the distribution of each parameter from a chain stored in a
    fits file. 
    """
    din=pyfits.open(fnamein)[1]
    for pname in din.get_coldefs().names:
        plotSinlgeParDist(din,
                          pname,
                          os.path.join(dirout, 
                                       "p%s-dist.eps" % (pname,)),
                          burn=burn)

    
                

def TestMetro():

    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.02,
                        nsample=10,
                        fnameout_chain="temp/t.fits")

def TestMetroIC(c,r,
                nzern=5,
                nsample=20000,
                multiamp=False):
    fnameout="temp/metro_ic_p%i%i_z%i.fits" % (c,r,nzern)
    plotdir = "temp/ic_p%i%i_z%i" % (c,r,nzern)
    r=MetroMustang("td/t18-raw-%i-%i-db.fits" % (c,r), 
                   amp_sigma=0.00001,
                   z_sigma=0.1,
                   nsample=nsample,
                   ic="oofout/t18-raw-%i-%i-db-000/z%i/fitpars.fits" % (c,r,nzern),
                   fnameout_chain=fnameout,
                   nzern=nzern,
                   multiamp=multiamp)
    plotParDist(fnameout, plotdir)
    return r

def TestMetroIC_V2(c,r,
                   nzern=5,
                   nsample=20000,
                   multiamp=False,
                   ic_v=2):
    fnameout="temp/metro_ic_p%i%i_z%i_ic%i-v2.fits" % (c,r,nzern,ic_v)
    plotdir = "temp/ic_p%i%i_z%i-v2" % (c,r,nzern)
    if ic_v is 2:
        ic="oofout/t18-raw-%i-%i-v2-db-000/z%i/fitpars.fits" % (c,r,nzern)
    elif ic_v is 1:
        ic="oofout/t18-raw-%i-%i-db-000/z%i/fitpars.fits" % (c,r,nzern)
    elif ic_v is 0:
        #Well, need to at least load amp, and offsets so we are not
        #hunting around for ever to burn in
        ic="oofout/t18-raw-%i-%i-v2-db-000/z%i/fitpars.fits" % (c,r,1)
        
    r=MetroMustang("td/t18-raw-%i-%i-v2-db.fits" % (c,r), 
                   amp_sigma=0.00001,
                   z_sigma=0.1,
                   nsample=nsample,
                   ic=ic,
                   fnameout_chain=fnameout,
                   nzern=nzern,
                   multiamp=multiamp)
    plotParDist(fnameout, plotdir)
    return r




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

