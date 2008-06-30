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
                 ic=None):
    """
    Sample posterior distribution given MUSTANG data using the
    Metropolis MCMC algorithm
    """
    
    oc=oofreduce.MkObsCompare( fnamein, 
                               nzern=5)

    sigmas=pybnmin1.DoubleVector([ amp_sigma]+ [z_sigma]*20 )

    metro=pybnmin1.MetropolisMCMC(oc.downcast(),
                                  sigmas,
                                  33)
    if ic is not None:
        bnmin1io.FLoad(ic)
    else:
        metro.getbyname("amp").setp(0.0001)
    return metro.sample(nsample)    
    

def TestMetro():

    return MetroMustang("td/t18-raw-5-3-db.fits", 
                        amp_sigma=0.00001,
                        z_sigma=0.02,
                        nsample=10000)

