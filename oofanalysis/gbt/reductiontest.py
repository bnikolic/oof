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
                               nzern=5,
                               npix=256,
                               oversample=4.0,
                               ds_fwhm=1.0,
                               ds_extent=2.0)

    sigmas=oofreduce.pybnmin1.DoubleVector([ 0.000003]+ [0.01]*20 +[ 0.001] )

    metro=oofreduce.pybnmin1.MetropolisMCMC(oc.downcast(),
                                            sigmas,
                                            33)
    metro.getbyname("amp").setp(0.00085)
    metro.getbyname("z2").setp(-6.2)
    metro.getbyname("sigma").setp(0.3)
    metro.getbyname("beamgainf").setp(1.08)
    metro.getbyname("beamgainf").dofit=1
    return metro.sample(10000)
    


