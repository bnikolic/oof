# Bojan Nikolic <bojan@bnikolic.co.uk>
# 2007
#
# Test the reduction runs finely

from setup import *

import oofreduce
import oofplot

sample="/home/bn204/d/data/oof/gbt/ver001/0411/s114-l-db.fits"

oofreduce.Red( "/home/bnikolic/data/gbt-oof/q-band/old/s114-l-db.fits", extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0, nzmax=5)
