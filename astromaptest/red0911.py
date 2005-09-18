# Bojan Nikolic
# $Id: red0911.py,v 1.2 2005/09/18 17:05:00 bnikolic Exp $
#
# Reduce oof holography data taken on 0911

import os

import oofreduce

scanlist = [6 , 14 , 29,  37 , 45, 53 ,69, 77, 85, 93, 101 ]

datadir="/users/bnikolic/d/astrodata/gbtoof/2005/ver001/0911"

def red():
    for sno in scanlist:
        oofreduce.Red(os.path.join(datadir, "s%i-l-db.fits" % sno),
                      extrafit=[ "beamgainf" ],
                      extraic =[ ("z2" , -6.2),
                                 ( "sigma" , 0.3 )],
                      npix=256,
                      oversample=4.0,
                      ds_fwhm=1.0,
                      ds_extent=2.0,
                      nzmax=5,
                      prefdirout="oofout0911")

def doplot():
    for sno in scanlist:
        oofplot.PlotDir("oofout0911/s%i-l-db-000/z5" %sno,
                        bbox=[ -1e-3, 1e-3, -1e-3, 1e-3],
                        hardcopy=True)


