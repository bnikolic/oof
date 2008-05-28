# Bojan Nikolic <bojan@bnikolic.co.uk>
# 2007
#
# Test the reduction runs finely

from setup import *

import oofreduce
import oofplot

sample="/home/bn204/d/data/oof/gbt/ver001/0411/s114-l-db.fits"

janq= "/home/bnikolic/data/gbt-oof/q-band/TPAR_18_red/s39-l-db.fits"

if 0:
    oofreduce.Red( "/home/bnikolic/data/gbt-oof/q-band/old/s114-l-db.fits", extrafit=[ "beamgainf" ],
                          extraic =[ ("z2" , -6.2),
                                     ( "sigma" , 0.3 )],
                          npix=256,
                          oversample=4.0,
                          ds_fwhm=1.0,
                          ds_extent=2.0, nzmax=5)

if 0:
    oofreduce.Red( sample,
                   extrafit=[ "beamgainf",
                              "sigma",
                              "x0",
                              "y0"],
                   extraic =[ ("z2" , -6.2),
                              ( "sigma" , 0.3 )],
                   npix=256,
                   oversample=4.0,
                   ds_fwhm=1.0,
                   ds_extent=2.0, nzmax=7)    


def TestMetro():
    
    oc=oofreduce.MkObsCompare( "/home/bnikolic/data/gbt-oof/q-band/old/s114-l-db.fits", 
                               nzern=1,
                               npix=256,
                               oversample=4.0,
                               ds_fwhm=1.0,
                               ds_extent=2.0)

    sigmas=oofreduce.pybnmin1.DoubleVector([ 0.0001 , 0.1, 0.1])

    metro=oofreduce.pybnmin1.MetropolisMCMC(oc.downcast(),
                                            sigmas,
                                            33)
    metro.getbyname("amp").setp(0.000853)
    metro.getbyname("z2").setp(-6.2)

    return metro.sample(1000)
    


