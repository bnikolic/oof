# Bojan Nikolic  <bojan@bnikolic.co.uk>, <b.nikolic@mrao.cam.ac.uk>
#
# Investigate MUSTANG OOF data using the Metropolis MCMC algorithm

import setup

import pybnmin1
import bnmin1utils

import oofreduce


def TestMetro():

    oc=oofreduce.MkObsCompare( "td/t18-raw-5-3-db.fits", 
                               nzern=5)

    sigmas=oofreduce.pybnmin1.DoubleVector([ 0.00001]+ [0.05]*20 )

    metro=oofreduce.pybnmin1.MetropolisMCMC(oc.downcast(),
                                            sigmas,
                                            33)
    metro.getbyname("amp").setp(0.0001)
    return metro.sample(100)    
